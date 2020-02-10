//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.h
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

#include "Component.h"	// base class
#include "Vector2D.h"	// Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;
class Animator;
class Sprite;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class MonkeyMovement : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Constructor
    MonkeyMovement();

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

    // Moves horizontally based on input
    void MoveHorizontal() const;

    // Moves vertically based on input
    void MoveVertical() const;

    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Movement properties
    float m_monkeyWalkSpeed;
    float m_monkeyJumpSpeed;
    float m_groundHeight;
    Beta::Vector2D m_gravity;

    // Components
    RigidBody* m_rigidBody;
    Animator* m_animator;
    Sprite* m_sprite;

    COMPONENT_CLASS_DECLARATIONS(MonkeyMovement)
};

//------------------------------------------------------------------------------
