//------------------------------------------------------------------------------
//
// File Name:	SoundManager.cpp
// Author(s):	Brandon Wolenetz
// Project:		Project 7
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SoundManager.h"

#include <iostream>
#include <fmod_errors.h>
#include <sstream>


//------------------------------------------------------------------------------

const unsigned strBufSize = 128;


//------------------------------------------------------------------------------
// Local Functions:
//------------------------------------------------------------------------------
bool FMOD_Assert(FMOD_RESULT result, const bool throwExeptionIfFail) {
    if (result != FMOD_OK) {
        std::cerr << "FMOD ERROR! (" << result << "): " << FMOD_ErrorString(result) << std::endl;
        
        if (throwExeptionIfFail) {
            std::stringstream sstream;
            sstream << "FAILED TO INITIALIZE FMOD (" << result << "): " << FMOD_ErrorString(result);
            throw sstream.str();
        }
        
        return false;
    }
    return true;
}


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


// Constructor - initializes FMOD.
SoundManager::SoundManager() :
    BetaObject("SoundManager"), musicVolume(1.0f), effectsVolume(1.0f), audioFilePath("Audio/"),
    bankFilePath("Banks/"), eventPrefix("event:/"),
    musicChannel(nullptr), effectsChannelGroup(nullptr), system(nullptr), studioSystem(nullptr) {

    FMOD_Assert(FMOD::Studio::System::create(&studioSystem), true);
    FMOD_Assert(studioSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0), true);

    FMOD_Assert(studioSystem->getLowLevelSystem(&system), true);
    FMOD_Assert(system->createChannelGroup("SoundEffects", &effectsChannelGroup), true);

}

// Destructor
SoundManager::~SoundManager() {
    FMOD_Assert(studioSystem->release());
}

// Update the FMOD system.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SoundManager::Update(float dt) {
    UNREFERENCED_PARAMETER(dt);

    FMOD_Assert(studioSystem->update());
}

// Shutdown the sound manager.
void SoundManager::Shutdown(void) {
    for (size_t i = 0; i < soundList.Size(); ++i) {
        FMOD_Assert(soundList[i]->release());
    }
    soundList.Clear();
    for (size_t i = 0; i < bankList.Size(); ++i) {
        FMOD_Assert(bankList[i]->unload());
    }
    bankList.Clear();
}

// Creates a non-looping FMOD sound.
// Params:
//	 filename = Name of the sound file (WAV).
void SoundManager::AddEffect(const std::string& filename) {
    AddSound(filename, FMOD_DEFAULT);
}

// Creates an FMOD stream for a music file.
// Params:
//	 filename = Name of the music file (MP3).
void SoundManager::AddMusic(const std::string& filename) {
    AddSound(filename, FMOD_DEFAULT | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
}

// Creates an FMOD sound bank
// Params:
//   filename = Name of the FMOD bank file.
void SoundManager::AddBank(const std::string& filename) {
    std::stringstream path;
    path << "Assets/" << audioFilePath << bankFilePath << filename;

    FMOD::Studio::Bank* bank;

    FMOD_Assert(studioSystem->loadBankFile(path.str().c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));

    //print bank info ---------------------------------

    std::cout << "LOADED BANK: " << path.str() << std::endl;

    int eventCount;
    FMOD_Assert(bank->getEventCount(&eventCount));
    
    std::cout << "Containing " << eventCount << " Events" << std::endl;

    //-------------------------------------------------

    bankList.push_back(bank);
}

// Plays a sound with the specified name.
// Params:
//	 name = The name of the sound to be played.
// Return:
//   The channel that was used to play the given sound.
FMOD::Channel* SoundManager::PlaySound(const std::string& soundName) {

    char strBuf[strBufSize];
    FMOD_MODE mode;

    for (size_t i = 0; i < soundList.Size(); ++i) {
        FMOD_Assert(soundList[i]->getName(strBuf, strBufSize));
        if (strcmp(strBuf, soundName.c_str()) != 0)
            continue;
        
        FMOD_Assert(soundList[i]->getMode(&mode));

        if (mode & FMOD_CREATESTREAM) {
            return PlayMusic(soundList[i]);
        }
        return PlayEffect(soundList[i]);
    }
    return nullptr;
}

// Starts an audio event with the given name.
// The event must be in one of the loaded banks.
// Params:
//	 name = The name of the event that will be started.
FMOD::Studio::EventInstance* SoundManager::PlayEvent(const std::string& soundName) {

    std::stringstream eventName;
    eventName << eventPrefix << soundName;

    FMOD::Studio::EventDescription* description;
    FMOD::Studio::EventInstance* instance;

    FMOD_Assert(studioSystem->getEvent(eventName.str().c_str(), &description));
    FMOD_Assert(description->createInstance(&instance));

    FMOD_Assert(instance->start());

    FMOD_Assert(instance->release());

    return instance;

}

// Set the volume of the music channel.
// Params:
//	 volume = New value for the music volume (0.0 to 1.0).
void SoundManager::SetMusicVolume(float volume) {
    musicVolume = volume;
    if (musicChannel != nullptr) {
        FMOD_Assert(musicChannel->setVolume(volume));
    }
}

// Set the volume of the sound effects channel group.
// Params:
//	 volume = New value for the FX volume (0.0 to 1.0).
void SoundManager::SetEffectsVolume(float volume) {
    effectsVolume = volume;
     FMOD_Assert(effectsChannelGroup->setVolume(volume));
}

// Get the volume of the music channel.
// Return:
//	 volume = Current value for the music volume.
float SoundManager::GetMusicVolume() const {
    return musicVolume;
}

// Get the volume of the sound effects channel group.
// Return:
//	 volume = Current value for the FX volume.
float SoundManager::GetEffectsVolume() const {
    return effectsVolume;
}

// Stop the current music
void SoundManager::StopMusic() {
    if (musicChannel != nullptr) {
        FMOD_Assert(musicChannel->stop());
        musicChannel = nullptr;
    }
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

//TODO: this part...

// Different behaviors for SFX vs BGM
FMOD::Channel* SoundManager::PlayEffect(FMOD::Sound* sound) const {
    FMOD::Channel* channel;

    FMOD_Assert(system->playSound(sound, effectsChannelGroup, false, &channel));

    return channel;
}
FMOD::Channel* SoundManager::PlayMusic(FMOD::Sound* sound) {
    StopMusic();

    FMOD_Assert(system->playSound(sound, nullptr, false, &musicChannel));

    return musicChannel;
}

// Add FX/BGM helper
void SoundManager::AddSound(const std::string& filename, FMOD_MODE mode) {
    std::stringstream path;
    path << "Assets/" << audioFilePath << filename;

    FMOD::Sound* sound;

    char strBuf[strBufSize];

    FMOD_Assert(system->createSound(path.str().c_str(), mode, nullptr, &sound));

    FMOD_Assert(sound->getName(strBuf, strBufSize));

    std::cout << "Loaded Sound: " << strBuf << " from: " << path.str() << std::endl;

    soundList.push_back(sound);
}



//------------------------------------------------------------------------------
