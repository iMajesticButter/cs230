//------------------------------------------------------------------------------
//
// File Name:	Behaviors.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Behaviors.h"

#include "Transform.h"
#include "RigidBody.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

namespace Behaviors {
    // ship movement settigs
    const float TurnSpeed = 2.5f;
    const float MoveThrust = 2.0f;
    const float MaxSpeed = 5.0f;
    const float StoppingDistance = 1.0f;
    const float StoppingSpeed = 0.1f;
    const float FaceingError = 0.1f;
    const float drag = 2.0f;

    // Movement behavior for the triangle/ship.
    // Params:
    //	 transform = The transform component of the ship.
    //   rigidBody = The rigid body of the ship.
    void UpdateShip(Transform* transform, RigidBody* rigidBody) {
        using namespace Beta;

        //get mouse pos
        Input* input = EngineGetModule(Input);
        GraphicsEngine* gEngine = EngineGetModule(GraphicsEngine);

        Vector2D mousePos = gEngine->GetDefaultCamera().ScreenToWorldPosition(input->GetCursorPosition());


        //get vector from ship to mouse
        Vector2D mouseVec = mousePos - transform->GetTranslation();

        //get dot product from left vector and mouse vector
        float dot = mouseVec.DotProduct(transform->Left());
        float absDot = abs(dot);

        //rotate to mouse
        float angVel = 0;

        //to stop the triangle from snap-turning
        float speedFalloff = absDot < 1 ? absDot : 1;

        if (dot < 0) {
            angVel = TurnSpeed * speedFalloff;
        } else if (dot > 0) {
            angVel = -TurnSpeed * speedFalloff;
        }

        //movement
        if (absDot <= FaceingError) {
            //stop turning
            angVel = 0;

            //move if outside stopping distance
            if (transform->GetTranslation().Distance(mousePos) > StoppingDistance) {

                rigidBody->AddForce(transform->Forward() * MoveThrust);

                // limit speed
                if (rigidBody->GetVelocity().Magnitude() > MoveThrust) {
                    rigidBody->SetVelocity(rigidBody->GetVelocity().Normalized() * MoveThrust);
                }
            }
        }

        //rough drag
        if (transform->GetTranslation().Distance(mousePos) <= StoppingDistance) {
            rigidBody->AddForce(rigidBody->GetVelocity().Normalized() * -drag * rigidBody->GetVelocity().Magnitude());
            if (rigidBody->GetVelocity().Magnitude() < StoppingSpeed) {
                rigidBody->SetVelocity(Vector2D(0, 0));
            }
        }

        //apply angular velocity
        rigidBody->SetAngularVelocity(angVel);


    }

    // monkey movement settigs
    const float MoveSpeed = 1.5f;
    const float GravityForce = 9.81f;
    const float JumpForce = 500.0f;

    // Movement behavior for the monkey.
    // Params:
    //	 transform = The transform component of the monkey.
    //   rigidBody = The rigid body of the monkey.
    void UpdateMonkey(Transform* transform, RigidBody* rigidBody) {
        
        using namespace Beta;

        Input* in = EngineGetModule(Input);

        //movement (left/right)
        float xVel = 0.0f;
        float yVel = rigidBody->GetVelocity().y;

        if (in->CheckHeld('A')) {
            xVel -= MoveSpeed;
        }
        if (in->CheckHeld('D')) {
            xVel += MoveSpeed;
        }


        //detect if monkey is on the ground
        bool onGround = false;
        
        //get ground world position
        Vector2D screenRes = EngineGetModule(GraphicsEngine)->GetDefaultCamera().ScreenToWorldPosition(EngineGetModule(WindowSystem)->GetResolution());

        float floorY = screenRes.y * 0.5f;
        floorY -= transform->GetScale().y * 0.75f;

        if (transform->GetTranslation().y <= floorY) {
            onGround = true;
            transform->SetTranslation(Vector2D(transform->GetTranslation().x, floorY));
            yVel = 0;
        }

        //jumping
        if (onGround && in->CheckHeld(VK_SPACE)) {
            rigidBody->AddForce(Vector2D(0, JumpForce));
        }

        //gravity
        rigidBody->AddForce(Vector2D(0, -GravityForce));

        //apply movement
        rigidBody->SetVelocity(Vector2D(xVel, yVel));
        

    }
}