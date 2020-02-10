//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "MonkeyMovement.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Sprite.h"


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
MonkeyMovement::MonkeyMovement() : Component("MonkeyMovement"), 
            m_monkeyWalkSpeed(2.0f), m_monkeyJumpSpeed(200.0f), m_groundHeight(-2.0f), 
            m_gravity(Beta::Vector2D(0, -9.81f)), m_rigidBody(nullptr) {

}

// Initialize this component (happens at object creation).
void MonkeyMovement::Initialize() {
    m_rigidBody = GetComponent<RigidBody>();
    m_animator = GetComponent<Animator>();
    m_sprite = GetComponent<Sprite>();
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void MonkeyMovement::Update(float dt) {
    UNREFERENCED_PARAMETER(dt);
    MoveHorizontal();
    MoveVertical();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Moves horizontally based on input
void MonkeyMovement::MoveHorizontal() const {

    auto input = EngineGetModule(Beta::Input);

    float horizMove = 0;

    if (input->CheckHeld('A')) {
        --horizMove;
    }
    if (input->CheckHeld('D')) {
        ++horizMove;
    }

    m_rigidBody->SetVelocity(Beta::Vector2D(horizMove * m_monkeyWalkSpeed, m_rigidBody->GetVelocity().y));

    if (horizMove == 0) {
        m_animator->Play(0, 1, false);
    } else if(m_animator->IsDone()) {
        m_animator->Play(0, 1, true);
    }

    if (horizMove > 0) {
        m_sprite->FlipX(false);
    } else if (horizMove < 0) {
        m_sprite->FlipX(true);
    }

}

// Moves vertically based on input
void MonkeyMovement::MoveVertical() const {

    m_rigidBody->AddForce(m_gravity);

    auto input = EngineGetModule(Beta::Input);

    if (transform()->GetTranslation().y <= m_groundHeight) {
        transform()->SetTranslation(Beta::Vector2D(transform()->GetTranslation().x, m_groundHeight));
        m_rigidBody->SetVelocity(Beta::Vector2D(m_rigidBody->GetVelocity().x, 0.0f));

        if (input->CheckHeld(' ')) {
            m_rigidBody->AddForce(Beta::Vector2D(0, m_monkeyJumpSpeed));
        }
    }
}

COMPONENT_CLASS_DEFINITIONS(MonkeyMovement)