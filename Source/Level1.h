//------------------------------------------------------------------------------
//
// File Name:	Level1.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Level.h"

namespace Beta {
    class Mesh;
}

class Sprite;
class Transform;
class RigidBody;
class SoundManager;

namespace FMOD {
    class Channel;
}


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels {
	class Level1 : public Level {
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 1.
		Level1();

		// Load the resources associated with Level 1.
		void Load();

		// Initialize the memory associated with Level 1.
		void Initialize();

		// Update Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt);

        //shutdown the level
        void Shutdown();

		// Unload the resources associated with Level 1.
		void Unload();

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

        Beta::Mesh* m_mesh;

        SoundManager* m_soundManager;
        FMOD::Channel* m_music;

	};
}

//----------------------------------------------------------------------------
