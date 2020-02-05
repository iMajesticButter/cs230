//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Archetypes.h"

#include "GameObject.h"
#include "Space.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Transform.h"
#include "PlayerShip.h"
#include "TimedDeath.h"
#include "Animator.h"
#include "MonkeyMovement.h"

namespace Archetypes {
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Create the ship game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateShip(Beta::Mesh* mesh) {
        GameObject* ship = new GameObject("Ship");

        ship->transform()->SetScale(Beta::Vector2D(0.5f, 0.5f));

        ship->AddComponent<Sprite>(nullptr, mesh);
        ship->AddComponent<RigidBody>();
        ship->AddComponent<PlayerShip>();

        return ship;
    }

    // Create the archetype for the bullet object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateBulletArchetype(Beta::Mesh* mesh) {
        GameObject* bullet = new GameObject("Bullet");

        bullet->transform()->SetScale(Beta::Vector2D(0.07f, 0.07f));

        bullet->AddComponent<Sprite>(nullptr, mesh);
        bullet->AddComponent<RigidBody>();
        bullet->AddComponent<TimedDeath>();

        return bullet;
    }

    // Create the monkey game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    //   spriteSource = The sprite source to use for the object.
    //   animatino = The walk animation.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateMonkey(Beta::Mesh* mesh, SpriteSource* spriteSource, Animation* animation) {
        GameObject* monkey = new GameObject("Monkey");

        monkey->AddComponent<Sprite>(spriteSource, mesh);
        monkey->AddComponent<Animator>()->AddAnimation(animation);
        monkey->AddComponent<RigidBody>();
        monkey->AddComponent<MonkeyMovement>();

        return monkey;
    }
}