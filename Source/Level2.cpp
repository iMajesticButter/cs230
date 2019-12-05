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
#include "Space.h"

#include "SpriteSource.h"
#include "Sprite.h"

#include "MeshHelper.h"
#include "Animator.h"
#include "Animation.h"

namespace Levels {
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2() : Level("Level2"), lives(2), maxHealth(2) {
       
	}

	// Load the resources associated with Level 2.
	void Level2::Load() {
		std::cout << "Level2::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateQuadMesh(Beta::Vector2D(1.0f/3.0f, 1.0f/5.0f));

        m_tex = Beta::Texture::CreateTextureFromFile("Monkey.png");
        m_spriteSource = new SpriteSource(m_tex, "Monkey", 3, 5);

        m_animation = new Animation("test", m_spriteSource, 8, 0, 0.0f);


	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize() {
		std::cout << "Level2::Initialize" << std::endl;
		currentHealth = maxHealth;

        m_sprite = new Sprite(m_spriteSource, m_mesh);

        m_animator = new Animator(m_sprite);
        size_t index = m_animator->AddAnimation(m_animation);
        m_animator->Play(index, 1.0f, true);
    }

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt) {
		UNREFERENCED_PARAMETER(dt);
		std::cout << "Level2::Update" << std::endl;

        m_sprite->Draw();
        m_animator->Update(dt);

        if (!m_animator->IsDone())
            return;

        --currentHealth;
        if (currentHealth <= 0) {
            --lives;
            if (lives <= 0) {
                Beta::EngineCore::GetInstance().Stop();
            } else {
                GetSpace()->RestartLevel();
            }
        }
	}

	// Shutdown any memory associated with Level 2.
	void Level2::Shutdown() {
		std::cout << "Level2::Shutdown" << std::endl;

        delete m_animator;
        delete m_sprite;
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload() {
		std::cout << "Level2::Unload" << std::endl;

        delete m_animation;
        delete m_spriteSource;
        delete m_tex;
        delete m_mesh;
	}
}