//------------------------------------------------------------------------------
//
// File Name:	Level2.h
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
class Tilemap;

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

		// Unload the resources associated with Level 2.
		void Unload();

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

        Beta::Mesh* m_mesh;
        Beta::Texture* m_tex;

        Beta::Mesh* m_mapMesh;
        Beta::Texture* m_mapTex;
        SpriteSource* m_mapSpriteSource;

        SpriteSource* m_spriteSource;
        Animation* m_animation;
        Tilemap* m_tilemap;

	};
}

//----------------------------------------------------------------------------
