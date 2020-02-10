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

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // inheritance

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class PlayerShip : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Non-default constructor
    // Params:
    //   forwardThrust = Amount of force added to the ship when thrusters are activated.
    //   maximumSpeed  = Maximum attainable speed of the ship.
    //   rotationSpeed = Speed at which the ship rotates.
    //   bulletSpeed   = Speed at which bullets move when fired by ship.
    PlayerShip(float forwardThrust = 1.0f, float maximumSpeed = 2.0f,
               float rotationSpeed = 3.14f, float bulletSpeed = 1.5f);

    // Initialize this component (happens at object creation).
    void Initialize() override;

    // Update function for this component.
    // Params:
    //   dt = The (fixed) change in time since the last step.
    void Update(float dt) override;

private:
    //------------------------------------------------------------------------------
    // Private Functions:
    //------------------------------------------------------------------------------

    // Move forward when up arrow is pressed
    void Move() const;

    // Rotate when left or right arrow key is pressed
    void Rotate() const;

    // Shoot projectiles when space is pressed
    void Shoot() const;

    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Movement properties
    float m_forwardThrust;
    float m_maximumSpeed;
    float m_rotationSpeed;
    float m_bulletSpeed;

    // Components
    RigidBody* m_rigidBody;

    COMPONENT_CLASS_DECLARATIONS(PlayerShip)
};

//------------------------------------------------------------------------------
