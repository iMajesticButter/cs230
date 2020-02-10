//------------------------------------------------------------------------------
//
// File Name:	ColorChange.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ColorChange.h"
#include "Sprite.h"
#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"

//------------------------------------------------------------------------------

// Collision handler for ColorChange objects.
// Params:
//   object = The first object.
//   other  = The other object the first object is colliding with.
void ColorChangeCollisionHandler(GameObject& object, GameObject& other, Beta::Vector2D intersectVector) {
    UNREFERENCED_PARAMETER(intersectVector);
    UNREFERENCED_PARAMETER(other);

    object.GetComponent<ColorChange>()->m_collided = true;
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
// Params:
//   normalColor = The color that the object reverts to when not colliding.
//   collidedColor = The color that the object changes to when colliding.
//   collidedColorTime = The amount of time the object will retain the collided color.
ColorChange::ColorChange(const Beta::Color& normalColor, const Beta::Color& collidedColor, float collidedColorTime) :
    Component("ColorChange"), m_sprite(nullptr), m_normalColor(normalColor), m_collidedColor(collidedColor), m_collidedColorTime(collidedColorTime),
    m_collided(false), m_timer(0) {

}

// Initialize data for this object.
void ColorChange::Initialize() {
    m_sprite = GetComponent<Sprite>();

    auto collider = GetComponent<Collider>();
    if (collider != nullptr)
        collider->SetCollisionHandler(ColorChangeCollisionHandler);

    m_sprite->SetColor(m_normalColor);
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void ColorChange::Update(float dt) {
    if (m_collided) {

        m_sprite->SetColor(m_collidedColor);
        m_collided = false;
        m_timer = m_collidedColorTime;

    } else if(m_timer > 0) {

        m_timer -= dt;

        if (m_timer <= 0) {
            m_sprite->SetColor(m_normalColor);
        }
    }
}

COMPONENT_CLASS_DEFINITIONS(ColorChange)
