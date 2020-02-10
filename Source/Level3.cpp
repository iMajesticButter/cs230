//------------------------------------------------------------------------------
//
// File Name:	Level3.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level3.h"
#include "Level2.h"
#include "Level1.h"

#include "MeshHelper.h"
#include "SpriteSource.h"
#include "GameObject.h"
#include "Space.h"
#include "Archetypes.h"
#include "RigidBody.h"
#include "Transform.h"
#include "ScreenWrap.h"
#include "Collider.h"

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of Level 3.
Level3::Level3() : Level("Level3"), m_meshQuad(nullptr), m_spriteSourceCircle(nullptr), m_textureCircle(nullptr),
    m_circleSpeed(1.0f), m_pointSpeed(1.0f) {

}

// Load the resources associated with Level 3.
void Level3::Load() {
    m_meshQuad = Beta::MeshHelper::CreateQuadMesh();

    m_textureCircle = Beta::Texture::CreateTextureFromFile("Circle.png");
    m_spriteSourceCircle = new SpriteSource(m_textureCircle, "Circle", 1, 1);
}

// Initialize the memory associated with Level 3.
void Level3::Initialize() {

    auto rectStill = Archetypes::CreateRectangle(m_meshQuad);
    rectStill->GetComponent<RigidBody>()->SetMass(10);

    GetSpace()->GetObjectManager().AddObject(*rectStill);

    auto rectMoving = Archetypes::CreateRectangle(m_meshQuad);
    rectMoving->transform()->SetTranslation(Beta::Vector2D(0, 2));
    rectMoving->transform()->SetScale(Beta::Vector2D(1.5f, 0.5f));
    rectMoving->GetComponent<RigidBody>()->SetVelocity(Beta::Vector2D(3.0f, 1.5f));
    rectMoving->GetComponent<RigidBody>()->SetAngularVelocity(0.25f);
    rectMoving->GetComponent<RigidBody>()->SetMass(5);

    GetSpace()->GetObjectManager().AddObject(*rectMoving);

    auto circle = Archetypes::CreateCircle(m_meshQuad, m_spriteSourceCircle);
    circle->transform()->SetTranslation(Beta::Vector2D(0, -2));
    circle->GetComponent<RigidBody>()->SetMass(3.0f);
    GetSpace()->GetObjectManager().AddObject(*circle);

    auto circle2 = Archetypes::CreateCircle(m_meshQuad, m_spriteSourceCircle);
    circle2->transform()->SetTranslation(Beta::Vector2D(1.1f, -2));
    circle2->transform()->SetScale(Beta::Vector2D(0.5f, 0.5f));
    circle2->GetComponent<RigidBody>()->SetMass(2.0f);
    circle2->GetComponent<RigidBody>()->SetVelocity(Beta::Vector2D(-1.0f, 0.0f));
    GetSpace()->GetObjectManager().AddObject(*circle2);

    auto point = Archetypes::CreatePoint(m_meshQuad, m_spriteSourceCircle);
    point->transform()->SetTranslation(Beta::Vector2D(-2.1f, 0.0f));
    point->GetComponent<RigidBody>()->SetVelocity(Beta::Vector2D(0.0f, 1.0f));
    GetSpace()->GetObjectManager().AddObject(*point);

}

// Update Level 3.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level3::Update(float dt) {
    UNREFERENCED_PARAMETER(dt);

    auto input = EngineGetModule(Beta::Input);

    if (input->CheckTriggered('1')) {
        GetSpace()->SetLevel<Levels::Level1>();
    } else if (input->CheckTriggered('2')) {
        GetSpace()->SetLevel<Levels::Level2>();
    } else if (input->CheckTriggered('3')) {
        GetSpace()->RestartLevel();
    }

}

// Unload the resources associated with Level 3.
void Level3::Unload() {
    delete m_spriteSourceCircle;
    delete m_textureCircle;
    delete m_meshQuad;
}


//----------------------------------------------------------------------------
