//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright � 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Collider.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Tilemap;

namespace Beta {
    struct BoundingRectangle;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Enum for sides of bounding rectangle
enum class RectangleSide {
    SideBottom,
    SideTop,
    SideLeft,
    SideRight,

    // Number of sides
    SideCount,
};

// Tilemap collider class - goes on Tilemap object
class ColliderTilemap : public Collider {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Constructor for Tilemap collider.
    ColliderTilemap();

    // Debug drawing for colliders.
    void Draw() override;

    // Check for collision between a tilemap and another arbitrary collider.
    // Params:
    //	 other = Reference to the second collider component.
    // Returns:
    //	 Return the results of the collision check.
    bool IsCollidingWith(const Collider& other) const override;

    // Sets the tilemap to use for this collider.
    // Params:
    //   map = A pointer to the tilemap resource.
    void SetTilemap(const Tilemap* map);

    // Get the colliders aabb
    Beta::BoundingRectangle GetAABB() const override;

private:
    //------------------------------------------------------------------------------
    // Private Functions:
    //------------------------------------------------------------------------------

    // Checks whether the specified side of a given rectangle is colliding with the tilemap.
    // Params:
    //   rectangle = The bounding rectangle for an object.
    //   side = The side that needs to be tested for collision.
    // Returns:
    //   True if there is a collision, false otherwise.
    bool IsSideColliding(const Beta::BoundingRectangle& rectangle, RectangleSide side) const;

    // Determines whether a point is within a collidable cell in the tilemap.
    // Params:
    //   x = The x component of the point, in world coordinates.
    //   y = The y component of the point, in world coordinates.
    // Returns:
    //   False if the point is outside the map or the map is empty at that position, 
    //   or true if there is a tile at that position.
    bool IsCollidingAtPosition(float x, float y) const;

    // Moves an object and sets its velocity based on where it collided with the tilemap.
    // Params:
    //   objectRectangle = A bounding rectangle that encompasses the object.
    //   objectTransform = Pointer to the object's transform component.
    //   objectRigidBody = Pointer to the object's rigidBody component.
    //   collisions = True/false values from map collision checks.
    void ResolveCollisions(const Beta::BoundingRectangle& objectRectangle, Transform* objectTransform,
                           RigidBody* objectRigidBody, const MapCollision& collisions) const;

    // Returns the center of the next tile on the x-axis or y-axis.
    // Used for assisting in collision resolution on a particular side.
    // Params:
    //   side = Which side the collision is occurring on.
    //   sidePosition = The x or y value of that side.
    // Returns:
    //   The center of the next tile for the given position on the given side.
    float GetNextTileCenter(RectangleSide side, float sidePosition) const;

    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // The tilemap
    const Tilemap* m_map;

    COMPONENT_SUBCLASS_DECLARATIONS(ColliderTilemap)
};

//------------------------------------------------------------------------------
