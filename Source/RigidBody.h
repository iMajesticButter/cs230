//------------------------------------------------------------------------------
//
// File Name:	RigidBody.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class RigidBody {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Constructor
    // Params:
    //   transform - The transform of the object.
    RigidBody(Transform* transform);

    // Reset acceleration.
    // Params:
    //	 dt = Change in time (in seconds) since the last game loop.
    void Update(float dt);

    // Update velocity and translation.
    // Params:
    //	 dt = Change in time (in seconds) since the last fixed update.
    void FixedUpdate(float dt);

    // Set the velocity of a rigid body.
    // Params:
    //	 velocity = Pointer to a velocity vector.
    void SetVelocity(const Beta::Vector2D& velocity);

    // Get the velocity of a rigid body.
    // Returns:
    //		A reference to the component's velocity structure.
    const Beta::Vector2D& GetVelocity() const;

    // Set the angular velocity of a rigid body.
    // Params:
    //	 velocity = New value for the rotational velocity.
    void SetAngularVelocity(float velocity);

    // Get the angular velocity of a rigid body.
    // Returns:
    //	 A float representing the new angular velocity.
    float GetAngularVelocity() const;

    // Set the mass of the rigid body.
    // Params:
    //   mass = The new mass of the rigid body.
    void SetMass(float mass);

    // Add a force to the object.
    // Params:
    //	 force = A force vector with direction and magnitude.
    void AddForce(const Beta::Vector2D& force);

    // Get the acceleration of a rigid body.
    // Returns:
    //	 A reference to the component's acceleration structure.
    const Beta::Vector2D& GetAcceleration() const;

    // Get the old translation (position) of a rigid body.
    // Returns: 
    //   A reference to the component's oldTranslation structure,
    const Beta::Vector2D& GetOldTranslation() const;

private:
    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Velocity may be stored as a direction vector and speed scalar, instead.
    Beta::Vector2D	m_velocity;

    // Angular velocity, the speed and direction that the object rotates.
    float		m_angularVelocity;

    // Used when calculating acceleration due to forces.
    float		m_inverseMass;

    // The sum of all forces acting on an object
    Beta::Vector2D	m_forcesSum;

    // Acceleration = inverseMass * (sum of forces)
    Beta::Vector2D	m_acceleration;

    // Previous position.  May be used for resolving collisions.
    Beta::Vector2D	m_oldTranslation;

    // Transform component
    Transform* m_transform;
};
//------------------------------------------------------------------------------
