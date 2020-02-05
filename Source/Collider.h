//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;
class GameObject;
typedef void(*CollisionEventHandler)(GameObject& callingObject, GameObject& otherObject, Beta::Vector2D intersectVector);

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

enum class ColliderType {
    ColliderTypePoint,
    ColliderTypeCircle,
    ColliderTypePolygon
};

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Collider class - Detects collisions between objects
class Collider : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Allocate a new collider component.
    // Params:
    //   type = The type of collider (see the ColliderType enum).
    Collider(ColliderType type);

    // Set component pointers.
    void Initialize() override;

    // Draw collision shape
    virtual void Draw() = 0;

    // Check if two objects are colliding and send collision events.
    // Params:
    //	 other = Reference to the second collider component.
    void CheckCollision(const Collider& other);

    // Perform intersection test between two arbitrary colliders.
    // Params:
    //	 other = Reference to the second collider component.
    virtual bool IsCollidingWith(const Collider& other) const = 0;

    // Get the type of this component.
    //  (had to change this as it conflicted with GetType() in component class)
    ColliderType GetColliderType() const;

    // Sets the collision handler function for the collider.
    // Params:
    //   handler = A pointer to the collision handler function.
    void SetCollisionHandler(CollisionEventHandler handler);

protected:
    // Component pointers
    RigidBody* m_rigidBody;

    // Intersect vector
    Beta::Vector2D m_intersectVector;

private:
    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // The type of collider used by this component.
    ColliderType m_type;

    // Function pointer for collision handler
    CollisionEventHandler m_handler;
};

//------------------------------------------------------------------------------
