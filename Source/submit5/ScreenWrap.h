//------------------------------------------------------------------------------
//
// File Name:	ScreenWrap.h
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

#include "Component.h" // base class

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ScreenWrap : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Default constructor
    ScreenWrap();

    // Initialize this component (happens at object creation).
    void Initialize() override;

    // Update function for this component.
    // Params:
    //   dt = The (fixed) change in time since the last step.
    void Update(float dt) override;

private:

    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Components
    RigidBody* m_rigidBody;


    COMPONENT_CLASS_DECLARATIONS(ScreenWrap)
};

//------------------------------------------------------------------------------
