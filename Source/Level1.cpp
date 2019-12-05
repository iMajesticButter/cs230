//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level1.h"
#include "Level2.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Sprite.h"

namespace Levels {
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level1::Level1() : Level("Level1"), lives(256), m_mesh(nullptr), m_sprite(nullptr) {
	}

	// Load the resources associated with Level 1.
	void Level1::Load() {
		std::cout << "Level1::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateTriangleMesh(Beta::Colors::Red, Beta::Colors::Green, Beta::Colors::Blue);


	}

	// Initialize the memory associated with Level 1.
	void Level1::Initialize() {
		std::cout << "Level1::Initialize" << std::endl;

        m_sprite = new Sprite(nullptr, m_mesh);


	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level1::Update(float dt) {
		UNREFERENCED_PARAMETER(dt);
		std::cout << "Level1::Update" << std::endl;
		--lives;
		if (lives <= 0)
			GetSpace()->SetLevel<Level2>();

        m_sprite->Draw();
	}

	// Shutdown any memory associated with Level 1.
	void Level1::Shutdown() {
		std::cout << "Level1::Shutdown" << std::endl;

        delete m_sprite;
	}

	// Unload the resources associated with Level 1.
	void Level1::Unload() {
		std::cout << "Level1::Unload" << std::endl;

        delete m_mesh;
	}

}