//------------------------------------------------------------------------------
//
// File Name:	Space.h
// Author(s):	Jeremy Kings
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "BetaObject.h"

#include "GameObjectManager.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Level;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Space : public Beta::BetaObject {
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor(s)
	Space(const std::string& name = "GameSpace");

	// Destructor
	~Space();

	// Updates the state manager and object manager.
	// Params:
	//   dt = The change in time since the last call to this function.
	void Update(float dt);

	// Shuts down the object manager
	void Shutdown();

	// Returns a boolean indicating whether objects in this space are paused.
	// Returns:
	//   True if the space is paused, false otherwise.
	bool IsPaused() const;

	// Returns the name of the level currently running in this space.
	const std::string& GetLevelName() const;

	// Pauses the space, preventing objects from being updated, but objects are still drawn.
	// Params:
	//   value = A true/false value that indicates whether the space should be paused.
	void SetPaused(bool value);

	// Sets the level that the space is using after unloading the current level.
	// Params:
	//   level = The next level that the space will be using.
	void SetLevel(Level* level);

	// Sets the level that the space is using after unloading the current level.
	// Templates:
	//   level = The next level that the space will be using.
	template<class level>
	void SetLevel() {
		SetLevel(new level);
	}

	// Restarts the current level (next level = current)
	void RestartLevel();

    // Retrieve the object manager
    GameObjectManager& GetObjectManager();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Updates current/next level pointers and calls shutdown/unload/load/init
	void ChangeLevel();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	bool m_paused;
	Level* m_currentLevel;
	Level* m_nextLevel;

    GameObjectManager m_objectManager;
};

//------------------------------------------------------------------------------
