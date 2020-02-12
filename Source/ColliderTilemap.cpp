//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ColliderTilemap.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor for Tilemap collider.
ColliderTilemap::ColliderTilemap() : Collider(ColliderType::ColliderTypeTilemap) {

}

// Debug drawing for colliders.
void ColliderTilemap::Draw() {
#ifdef _DEBUG

    auto debug = EngineGetModule(Beta::DebugDraw);

    Beta::BoundingRectangle aabb = GetAABB();

    Beta::Vector2D tl = aabb.center + Beta::Vector2D(+aabb.extents.x, +aabb.extents.y);
    Beta::Vector2D tr = aabb.center + Beta::Vector2D(+aabb.extents.x, -aabb.extents.y);
    Beta::Vector2D bl = aabb.center + Beta::Vector2D(-aabb.extents.x, +aabb.extents.y);
    Beta::Vector2D br = aabb.center + Beta::Vector2D(-aabb.extents.x, -aabb.extents.y);

    debug->AddLineToList(tl, tr, Beta::Colors::Violet);
    debug->AddLineToList(tr, br, Beta::Colors::Violet);
    debug->AddLineToList(br, bl, Beta::Colors::Violet);
    debug->AddLineToList(bl, tl, Beta::Colors::Violet);
    debug->EndLineList();

#endif
}

// Check for collision between a tilemap and another arbitrary collider.
// Params:
//	 other = Reference to the second collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderTilemap::IsCollidingWith(const Collider& other) const {



    m_intersectVector = Beta::Vector2D(0, 0);
}

// Sets the tilemap to use for this collider.
// Params:
//   map = A pointer to the tilemap resource.
void ColliderTilemap::SetTilemap(const Tilemap* map) {

}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Checks whether the specified side of a given rectangle is colliding with the tilemap.
// Params:
//   rectangle = The bounding rectangle for an object.
//   side = The side that needs to be tested for collision.
// Returns:
//   True if there is a collision, false otherwise.
bool ColliderTilemap::IsSideColliding(const Beta::BoundingRectangle& rectangle, RectangleSide side) const {

}

// Determines whether a point is within a collidable cell in the tilemap.
// Params:
//   x = The x component of the point, in world coordinates.
//   y = The y component of the point, in world coordinates.
// Returns:
//   False if the point is outside the map or the map is empty at that position, 
//   or true if there is a tile at that position.
bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const {

}

// Moves an object and sets its velocity based on where it collided with the tilemap.
// Params:
//   objectRectangle = A bounding rectangle that encompasses the object.
//   objectTransform = Pointer to the object's transform component.
//   objectRigidBody = Pointer to the object's rigidBody component.
//   collisions = True/false values from map collision checks.
void ColliderTilemap::ResolveCollisions(const Beta::BoundingRectangle& objectRectangle, Transform* objectTransform,
                                        RigidBody* objectRigidBody, const MapCollision& collisions) const {

}

// Returns the center of the next tile on the x-axis or y-axis.
// Used for assisting in collision resolution on a particular side.
// Params:
//   side = Which side the collision is occurring on.
//   sidePosition = The x or y value of that side.
// Returns:
//   The center of the next tile for the given position on the given side.
float ColliderTilemap::GetNextTileCenter(RectangleSide side, float sidePosition) const {

}

// Get the colliders aabb
Beta::BoundingRectangle GetAABB() {

}

COMPONENT_SUBCLASS_DEFINITIONS(Collider, ColliderTilemap)