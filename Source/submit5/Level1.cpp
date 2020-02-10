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
#include "Level3.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Sprite.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Behaviors.h"
#include "Archetypes.h"

namespace Levels {
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Creates an instance of Level 1.
    Level1::Level1() : Level("Level1"), m_mesh(nullptr) {
    }

    // Load the resources associated with Level 1.
    void Level1::Load() {
        std::cout << "Level1::Load" << std::endl;

        m_mesh = Beta::MeshHelper::CreateTriangleMesh(Beta::Colors::Red, Beta::Colors::Green, Beta::Colors::Blue);

        GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(m_mesh));

    }

    // Initialize the memory associated with Level 1.
    void Level1::Initialize() {
        std::cout << "Level1::Initialize" << std::endl;

        GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateShip(m_mesh));

    }

    // Update Level 1.
    // Params:
    //	 dt = Change in time (in seconds) since the last game loop.
    void Level1::Update(float dt) {
        UNREFERENCED_PARAMETER(dt);
        //std::cout << "Level1::Update" << std::endl;

        //level switching
        Beta::Input* in = EngineGetModule(Beta::Input);

        if (in->IsKeyDown('1')) {
            GetSpace()->RestartLevel();
        } else if (in->IsKeyDown('2')) {
            GetSpace()->SetLevel<Level2>();
        } else if (in->IsKeyDown('3')) {
            GetSpace()->SetLevel<Level3>();
        }
    }

    // Unload the resources associated with Level 1.
    void Level1::Unload() {
        std::cout << "Level1::Unload" << std::endl;

        delete m_mesh;
    }

}