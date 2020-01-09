//------------------------------------------------------------------------------
//
// File Name:	Level2.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Level.h"

//------------------------------------------------------------------------------

namespace Beta {
    class Mesh;
    class Texture;
}

class SpriteSource;
class Sprite;
class Animator;
class Animation;
class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels {
	class Level2 : public Level {
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 2.
		Level2();

		// Load the resources associated with Level 2.
		void Load();

		// Initialize the memory associated with Level 2.
		void Initialize();

		// Update Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt);

		// Shutdown any memory associated with Level 2.
		void Shutdown();

		// Unload the resources associated with Level 2.
		void Unload();

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

        Beta::Mesh* m_mesh;
        Beta::Texture* m_tex;

        Sprite* m_sprite;
        SpriteSource* m_spriteSource;
        Animator* m_animator;
        Animation* m_animation;
        Transform* m_transform;
        RigidBody* m_rb;

	};
}

//----------------------------------------------------------------------------
