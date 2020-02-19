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
#include "ColliderTilemap.h"


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// collision handler
void MonkeyCollisionHandler(GameObject& object, GameObject& other, Beta::Vector2D intersectVector) {
    if (other.GetComponent<ColliderTilemap>() != nullptr) {
        if (intersectVector.y < 0) {
            object.GetComponent<MonkeyMovement>()->m_onGround = true;
        }
    }
}

// Constructor
MonkeyMovement::MonkeyMovement() : Component("MonkeyMovement"), 
            m_monkeyWalkSpeed(2.0f), m_monkeyJumpSpeed(7.0f), m_groundHeight(-2.0f), 
            m_gravity(Beta::Vector2D(0, -9.81f)), m_rigidBody(nullptr), m_sprite(nullptr), m_animator(nullptr), m_onGround(false) {

}

// Initialize this component (happens at object creation).
void MonkeyMovement::Initialize() {
    m_rigidBody = GetComponent<RigidBody>();
    m_animator = GetComponent<Animator>();
    m_sprite = GetComponent<Sprite>();
    GetComponent<Collider>()->SetCollisionHandler(MonkeyCollisionHandler);
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
        m_sprite->SetFrame(12);
    } else if(m_animator->IsDone()) {
        m_animator->Play(0, 1, true);
    }

    if (!m_onGround) {
        m_animator->Play(0, 1, false);
        m_sprite->SetFrame(9);
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

    if (m_onGround) {
        m_onGround = false;
        if (input->CheckHeld(' ')) {
            m_rigidBody->ApplyImpulse(Beta::Vector2D(0, m_monkeyJumpSpeed));
        }
    }
}

COMPONENT_CLASS_DEFINITIONS(MonkeyMovement)