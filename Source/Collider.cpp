//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
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

#include "stdafx.h"

#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Collider class - Detects collisions between objects

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Allocate a new collider component.
// Params:
//   type = The type of collider (see the ColliderType enum).
Collider::Collider(ColliderType type) : Component("Collider"), 
        m_handler(nullptr), m_rigidBody(nullptr), m_type(type), m_intersectVector(0,0) {

}

// Set component pointers.
void Collider::Initialize() {
    m_rigidBody = GetComponent<RigidBody>();
}

// Check if two objects are colliding and send collision events.
// Params:
//	 other = Reference to the second collider component.
void Collider::CheckCollision(const Collider& other) {

    m_intersectVector = Beta::Vector2D(0, 0);

    if (IsCollidingWith(other)) {
        if (m_handler != nullptr) {
            m_handler(*GetOwner(), *other.GetOwner(), m_intersectVector);
        }

        if (other.m_handler != nullptr) {
            other.m_handler(*other.GetOwner(), *GetOwner(), -m_intersectVector);
        }
    }

}

// Get the type of this component.
//  (had to change this as it conflicted with GetType() in component class)
ColliderType Collider::GetColliderType() const {
    return m_type;
}

// Sets the collision handler function for the collider.
// Params:
//   handler = A pointer to the collision handler function.
void Collider::SetCollisionHandler(CollisionEventHandler handler) {
    m_handler = handler;
}

//------------------------------------------------------------------------------
