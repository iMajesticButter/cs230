//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------



#include "stdafx.h"

#include "TimedDeath.h"
#include "GameObject.h"



//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Non-default constructor
// Params:
//   timeUntilDeath = Amount of time until the object self-destructs.
TimedDeath::TimedDeath(float timeUntilDeath) : Component("TimedDeath"), m_timeUntilDeath(timeUntilDeath) {

}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void TimedDeath::Update(float dt) {
    m_timeUntilDeath -= dt;
    if (m_timeUntilDeath <= 0) {
        GetOwner()->Destroy();
    }
}

COMPONENT_CLASS_DEFINITIONS(TimedDeath)