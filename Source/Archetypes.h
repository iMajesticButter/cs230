//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;
class Space;
class SpriteSource;
class Animation;
class Tilemap;

namespace Beta {
	class Mesh;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Archetypes {
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
		
	// Create the ship game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateShip(Beta::Mesh* mesh);

	// Create the archetype for the bullet object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBulletArchetype(Beta::Mesh* mesh);

	// Create the monkey game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	//   animatino = The walk animation.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateMonkey(Beta::Mesh* mesh, SpriteSource* spriteSource, Animation* animation);

    // Create the circle game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    //   spriteSource = The sprite source to use for the object.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateCircle(Beta::Mesh* mesh, SpriteSource* spriteSource);

    // Create the point game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    //   spriteSource = The sprite source to use for the object.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreatePoint(Beta::Mesh* mesh, SpriteSource* spriteSource);

    // Create the rectangle game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateRectangle(Beta::Mesh* mesh);

    // Create a tilemap object
    // Params:
    //   mesh = The mesh to use for the sprite.
    //   spriteSource = The sprite source to use for the sprite.
    //   map = The map to use for tilemap related components.
    // Returns:
    //   A pointer to the newly constructed game object.
    GameObject* CreateTilemapObject(Beta::Mesh* mesh, SpriteSource* spriteSource, Tilemap* map);
}

//----------------------------------------------------------------------------
