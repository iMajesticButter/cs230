//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PlayerShip.h"
#include "Transform.h"
#include "Space.h"
#include "GameObjectManager.h"
#include "RigidBody.h"


// Non-default constructor
// Params:
//   forwardThrust = Amount of force added to the ship when thrusters are activated.
//   maximumSpeed  = Maximum attainable speed of the ship.
//   rotationSpeed = Speed at which the ship rotates.
//   bulletSpeed   = Speed at which bullets move when fired by ship.
PlayerShip::PlayerShip(float forwardThrust, float maximumSpeed,
           float rotationSpeed, float bulletSpeed) : Component("PlayerShip"), 
           m_forwardThrust(forwardThrust), m_maximumSpeed(maximumSpeed), m_rotationSpeed(rotationSpeed),
           m_bulletSpeed(bulletSpeed), m_rigidBody(nullptr) {

}

// Initialize this component (happens at object creation).
void PlayerShip::Initialize() {
    m_rigidBody = GetComponent<RigidBody>();
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerShip::Update(float dt) {
    UNREFERENCED_PARAMETER(dt);
    Move();
    Rotate();
    Shoot();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Move forward when up arrow is pressed
void PlayerShip::Move() const {

    auto input = EngineGetModule(Beta::Input);

    if (input->CheckHeld('W')) {
        m_rigidBody->AddForce(transform()->Forward() * m_forwardThrust);
    }

}

// Rotate when left or right arrow key is pressed
void PlayerShip::Rotate() const {

    auto input = EngineGetModule(Beta::Input);

    float angularVel = 0;

    if (input->CheckHeld('A')) {
        ++angularVel;
    }
    if (input->CheckHeld('D')) {
        --angularVel;
    }

    m_rigidBody->SetAngularVelocity(angularVel * m_rotationSpeed);

}

// Shoot projectiles when space is pressed
void PlayerShip::Shoot() const {
    
    auto input = EngineGetModule(Beta::Input);

    if (input->CheckTriggered(' ')) {

        //get the bullet archetype
        GameObject* bullet = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Bullet"));

        if (bullet != nullptr) {
            //set its position and velocity
            bullet->transform()->SetTranslation(transform()->GetTranslation() + (transform()->Forward() * (transform()->GetScale().x * 0.5f)));
            bullet->transform()->SetRotation(transform()->GetRotation());

            bullet->GetComponent<RigidBody>()->SetVelocity(transform()->Forward() * m_bulletSpeed + m_rigidBody->GetVelocity());

            //add the bullet to the object manager
            GetSpace()->GetObjectManager().AddObject(*bullet);

        }

    }

}

COMPONENT_CLASS_DEFINITIONS(PlayerShip)