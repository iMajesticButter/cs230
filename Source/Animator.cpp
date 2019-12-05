//------------------------------------------------------------------------------
//
// File Name:	Animator.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Animator.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Animation.h"

//! Construct a new animation controller object.
Animator::Animator(Sprite* sprite) :
    m_animationIndex(0), m_playbackSpeed(1.0f), m_running(false), m_looping(false),
    m_done(false), m_sprite(sprite) {

}

//! Update the animation.
/*!
  /param dt Change in time (in seconds) since the last game loop.
*/
void Animator::Update(float dt) {
    std::cout << "Animator::Update" << std::endl;

    if (!m_running)
        return;

    m_sprite->SetFrame(m_animationList[m_animationIndex]->GetCurrentFrameIndex(dt, m_playbackSpeed, m_looping, &m_done));
}

//! Play an animation.
/*!
  /param animationIndex The index of the animation to play.
  /param laybackSpeed The speed at which to play the animation.
  /param oop Whether the animation should go back to the beginning after it reaches the end.
*/
void Animator::Play(size_t animationIndex, float playbackSpeed, bool loop) {
    std::cout << "Animator::Play" << std::endl;

    if (animationIndex >= m_animationList.Size()) {
        return;
    }

    m_animationIndex = animationIndex;
    m_playbackSpeed = playbackSpeed;
    m_looping = loop;

    m_running = true;
    m_done = false;

    const Animation* anim = m_animationList[animationIndex];
    m_sprite->SetSpriteSource(anim->GetSpriteSource());
    m_sprite->SetFrame(anim->Play());
}

//! Add an animation to the controller.
/*!
  /param animation The animation resource that will be added to the controller.
  /returns The index of the animation in the controller, for use with the Play function.
*/
size_t Animator::AddAnimation(const Animation* animation) {
    m_animationList.PushBack(animation);
    return m_animationList.Size() - 1;
}

//! Get the index of the currently playing animation, for use with the Play function.
size_t Animator::GetCurrentAnimationIndex() const {
    return m_animationIndex;
}

//! Get the index of the animation with the specified name
/*!
  /param name The name of the animation for which the index was requested.
  /returns The index of the given animation if it was found, or 0.
*/
size_t Animator::GetAnimationIndex(const std::string& name) const {
    for (unsigned i = 0; i < m_animationList.Size(); ++i) {
        if (m_animationList[i]->GetName() == name)
            return i;
    }
    return 0;
}

//! Determine if the animation has reached the end of its sequence.
/*!
  /returns True if the animation is done, false otherwise.
*/
bool Animator::IsDone() const {
    return m_done;
}

//! Set the time to wait between frames for the currently playing animation.
/*!
  /param duration The amount of time to wait between frames (in seconds).
*/
void Animator::SetPlaybackSpeed(float speed) {
    m_playbackSpeed = speed;
}