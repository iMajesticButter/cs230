//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level1.h"
#include "Level2.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Sprite.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Behaviors.h"

namespace Levels {
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Creates an instance of Level 1.
    Level1::Level1() : Level("Level1"), m_mesh(nullptr), m_sprite(nullptr), m_transform(nullptr), m_rb(nullptr) {
    }

    // Load the resources associated with Level 1.
    void Level1::Load() {
        std::cout << "Level1::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateTriangleMesh(Beta::Colors::Red, Beta::Colors::Green, Beta::Colors::Blue);


    }

    // Initialize the memory associated with Level 1.
    void Level1::Initialize() {
        std::cout << "Level1::Initialize" << std::endl;

        m_transform = new Transform(Beta::Vector2D(0, 0), Beta::Vector2D(1, 1), 0.0f);
        m_sprite = new Sprite(nullptr, m_mesh, m_transform);
        m_rb = new RigidBody(m_transform);


    }

    // Update Level 1.
    // Params:
    //	 dt = Change in time (in seconds) since the last game loop.
    void Level1::Update(float dt) {
        UNREFERENCED_PARAMETER(dt);
        std::cout << "Level1::Update" << std::endl;

        //level switching
        Beta::Input* in = EngineGetModule(Beta::Input);

        if (in->IsKeyDown('1')) {
            GetSpace()->RestartLevel();
        } else if (in->IsKeyDown('2')) {
            GetSpace()->SetLevel<Level2>();
        }

        Behaviors::UpdateShip(m_transform, m_rb);
        m_rb->Update(dt);
        m_rb->FixedUpdate(dt);

        m_sprite->Draw();
    }

    // Shutdown any memory associated with Level 1.
    void Level1::Shutdown() {
        std::cout << "Level1::Shutdown" << std::endl;

        delete m_rb;
        delete m_sprite;
        delete m_transform;
    }

    // Unload the resources associated with Level 1.
    void Level1::Unload() {
        std::cout << "Level1::Unload" << std::endl;

        delete m_mesh;
    }

}