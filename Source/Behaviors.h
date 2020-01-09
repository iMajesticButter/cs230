//------------------------------------------------------------------------------
//
// File Name:	Behaviors.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

namespace Behaviors {

    // Movement behavior for the triangle/ship.
    // Params:
    //	 transform = The transform component of the ship.
    //   rigidBody = The rigid body of the ship.
    void UpdateShip(Transform* transform, RigidBody* rigidBody);

    // Movement behavior for the monkey.
    // Params:
    //	 transform = The transform component of the monkey.
    //   rigidBody = The rigid body of the monkey.
    void UpdateMonkey(Transform* transform, RigidBody* rigidBody);
}
