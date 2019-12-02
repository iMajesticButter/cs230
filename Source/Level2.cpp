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
	}

	// Initialize the memory associated with Level 2.
	void Level2::Initialize() {
		std::cout << "Level2::Initialize" << std::endl;
		currentHealth = maxHealth;
	}

	// Update Level 1.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level2::Update(float dt) {
		UNREFERENCED_PARAMETER(dt);
		std::cout << "Level2::Update" << std::endl;
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
	}

	// Unload the resources associated with Level 2.
	void Level2::Unload() {
		std::cout << "Level2::Unload" << std::endl;
	}
}