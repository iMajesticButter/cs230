//------------------------------------------------------------------------------
//
// File Name:	ScreenWrap.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ScreenWrap.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Space.h"

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
ScreenWrap::ScreenWrap() : Component("ScreenWrap"), m_rigidBody(nullptr) {

}

// Initialize this component (happens at object creation).
void ScreenWrap::Initialize() {

    m_rigidBody = GetComponent<RigidBody>();

}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void ScreenWrap::Update(float dt) {
    using namespace Beta;

    UNREFERENCED_PARAMETER(dt);

    Vector2D velocity = m_rigidBody->GetVelocity();
    Vector2D pos = transform()->GetTranslation();
    Vector2D scale = transform()->GetScale();

    Vector2D screenSize = EngineGetModule(GraphicsEngine)->GetDefaultCamera().GetScreenWorldDimensions().extents;

    if (velocity.x > 0 && pos.x > screenSize.x + scale.x) {
        transform()->SetTranslation(Vector2D(-screenSize.x - scale.x, pos.y));
    } else if (velocity.x < 0 && pos.x < -screenSize.x - scale.x) {
        transform()->SetTranslation(Vector2D(screenSize.x + scale.x, pos.y));
    }

    if (velocity.y > 0 && pos.y > screenSize.y + scale.y) {
        transform()->SetTranslation(Vector2D(pos.x, -screenSize.y - scale.y));
    } else if (velocity.y < 0 && pos.y < -screenSize.y - scale.y) {
        transform()->SetTranslation(Vector2D(pos.x, screenSize.y + scale.y));
    }
}

//------------------------------------------------------------------------------

COMPONENT_CLASS_DEFINITIONS(ScreenWrap)
