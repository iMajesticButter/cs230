//------------------------------------------------------------------------------
//
// File Name:	Level.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level.h"


// Creates a game state.
// Params:
//   name = Name to use for this state.
Level::Level(const std::string& name) : BetaObject(name) {

}

// Retrieve the space in which the level is running.
Space* Level::GetSpace() const {
	return (Space*)GetOwner();
}
