//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.h
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

#include "Component.h" // base class

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class TimedDeath : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Non-default constructor
    // Params:
    //   timeUntilDeath = Amount of time until the object self-destructs.
    TimedDeath(float timeUntilDeath = 3.0f);

    // Update function for this component.
    // Params:
    //   dt = The (fixed) change in time since the last step.
    void Update(float dt) override;

private:
    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Amount of time until the object self-destructs.
    float m_timeUntilDeath;

    COMPONENT_CLASS_DECLARATIONS(TimedDeath)
};

//------------------------------------------------------------------------------
