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
#include "Space.h"

#include "SpriteSource.h"
#include "Sprite.h"
#include "Transform.h"

#include "MeshHelper.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Behaviors.h"

namespace Levels {
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 2.
	Level2::Level2() : Level("Level2"), 
        m_animation(nullptr), m_animator(nullptr), m_mesh(nullptr), m_sprite(nullptr), m_spriteSource(nullptr), m_tex(nullptr), m_transform(nullptr), m_rb(nullptr) {
       
	}

	// Load the resources associated with Level 2.
	void Level2::Load() {
		std::cout << "Level2::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateQuadMesh(Beta::Vector2D(1.0f/3.0f, 1.0f/5.0f));

        m_tex = Beta::Texture::CreateTextureFromFile("Monkey.png");
        m_spriteSource = new SpriteSource(m_tex, "Monkey", 3, 5);

        m_animation = new Animation("test", m_spriteSource, 8, 0, 0.2f);


	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize() {
		std::cout << "Level2::Initialize" << std::endl;

        m_transform = new Transform(Beta::Vector2D(0, 0), Beta::Vector2D(1, 1), 0.0f);
        m_sprite = new Sprite(m_spriteSource, m_mesh, m_transform);
        m_rb = new RigidBody(m_transform);

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

        //level switching
        Beta::Input* in = EngineGetModule(Beta::Input);

        if (in->IsKeyDown('1')) {
            GetSpace()->SetLevel<Level1>();
        } else if (in->IsKeyDown('2')) {
            GetSpace()->RestartLevel();
        }

        Behaviors::UpdateMonkey(m_transform, m_rb);

        m_rb->Update(dt);
        m_rb->FixedUpdate(dt);

	}

	// Shutdown any memory associated with Level 2.
	void Level2::Shutdown() {
		std::cout << "Level2::Shutdown" << std::endl;

        delete m_animator;
        delete m_rb;
        delete m_sprite;
        delete m_transform;
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