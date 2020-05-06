//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level2.h"
#include "Level1.h"
#include "Level3.h"
#include "Space.h"

#include "SpriteSource.h"
#include "Sprite.h"
#include "Transform.h"

#include "MeshHelper.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Behaviors.h"
#include "Archetypes.h"
#include "Tilemap.h"

namespace Levels {
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2() : Level("Level2"), 
        m_animation(nullptr), m_mesh(nullptr), m_spriteSource(nullptr), m_mapSpriteSource(nullptr), m_tex(nullptr), m_mapTex(nullptr), m_tilemap(nullptr) {
       
	}

	// Load the resources associated with Level 2.
	void Level2::Load() {
		std::cout << "Level2::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateQuadMesh(Beta::Vector2D(1.0f, 1.0f));

        m_tex = Beta::Texture::CreateTextureFromFile("Monkey.png");
        m_spriteSource = new SpriteSource(m_tex, "Monkey", 3, 5);

        m_animation = new Animation("test", m_spriteSource, 8, 0, 0.08f);

        m_tilemap = Tilemap::CreateTilemapFromFile("Level2.txt");

        m_mapTex = Beta::Texture::CreateTextureFromFile("Tilemap.png");
        m_mapSpriteSource = new SpriteSource(m_mapTex, "tilemap", 4, 3);

	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize() {
		std::cout << "Level2::Initialize" << std::endl;

        GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateMonkey(m_mesh, m_spriteSource, m_animation));

        GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateTilemapObject(m_mesh, m_mapSpriteSource, m_tilemap));

    }

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt) {
		UNREFERENCED_PARAMETER(dt);
		//std::cout << "Level2::Update" << std::endl;

        //level switching
        Beta::Input* in = EngineGetModule(Beta::Input);

        if (in->CheckTriggered('1')) {
            GetSpace()->SetLevel<Level1>();
        } else if (in->CheckTriggered('2')) {
            GetSpace()->RestartLevel();
        } else if (in->CheckTriggered('3')) {
            GetSpace()->SetLevel<Level3>();
        }

	}

	// Unload the resources associated with Level 2.
	void Level2::Unload() {
		std::cout << "Level2::Unload" << std::endl;

        delete m_mapSpriteSource;
        delete m_mapTex;

        delete m_tilemap;

        delete m_animation;
        delete m_spriteSource;
        delete m_tex;
        delete m_mesh;
	}
}