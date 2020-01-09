//------------------------------------------------------------------------------
//
// File Name:	RigidBody.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "RigidBody.h"

#include "Transform.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
// Params:
//   transform - The transform of the object.
RigidBody::RigidBody(Transform* transform) : m_transform(transform), m_angularVelocity(0), m_velocity(0,0), m_inverseMass(1), m_forcesSum(0, 0) {
    m_oldTranslation = m_transform->GetTranslation();
}

// Reset acceleration.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void RigidBody::Update(float dt) {
    UNREFERENCED_PARAMETER(dt);
    m_acceleration = m_forcesSum * m_inverseMass;
    m_forcesSum = Beta::Vector2D(0, 0);
}

// Update velocity and translation.
// Params:
//	 dt = Change in time (in seconds) since the last fixed update.
void RigidBody::FixedUpdate(float dt) {
    m_velocity += m_acceleration * dt;
    m_oldTranslation = m_transform->GetTranslation();

    m_transform->SetTranslation(m_oldTranslation + m_velocity * dt);

    m_transform->SetRotation(m_transform->GetRotation() + m_angularVelocity * dt);
}

// Set the velocity of a rigid body.
// Params:
//	 velocity = Pointer to a velocity vector.
void RigidBody::SetVelocity(const Beta::Vector2D& velocity) {
    m_velocity = velocity;
}

// Get the velocity of a rigid body.
// Returns:
//		A reference to the component's velocity structure.
const Beta::Vector2D& RigidBody::GetVelocity() const {
    return m_velocity;
}

// Set the angular velocity of a rigid body.
// Params:
//	 velocity = New value for the rotational velocity.
void RigidBody::SetAngularVelocity(float velocity) {
    m_angularVelocity = velocity;
}

// Get the angular velocity of a rigid body.
// Returns:
//	 A float representing the new angular velocity.
float RigidBody::GetAngularVelocity() const {
    return m_angularVelocity;
}

// Set the mass of the rigid body.
// Params:
//   mass = The new mass of the rigid body.
void RigidBody::SetMass(float mass) {
    m_inverseMass = 1 / mass;
}

// Add a force to the object.
// Params:
//	 force = A force vector with direction and magnitude.
void RigidBody::AddForce(const Beta::Vector2D& force) {
    m_forcesSum += force;
}

// Get the acceleration of a rigid body.
// Returns:
//	 A reference to the component's acceleration structure.
const Beta::Vector2D& RigidBody::GetAcceleration() const {
    return m_acceleration;
}

// Get the old translation (position) of a rigid body.
// Returns: 
//   A reference to the component's oldTranslation structure,
const Beta::Vector2D& RigidBody::GetOldTranslation() const {
    return m_oldTranslation;
}

