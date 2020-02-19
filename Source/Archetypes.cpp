//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
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
#include "BoxCollider.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "CircleCollider.h"
#include "PointCollider.h"
#include "Tilemap.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"

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
        monkey->AddComponent<BoxCollider>(0.75f, 1.0f);

        return monkey;
    }


    // Create the circle game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    //   spriteSource = The sprite source to use for the object.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateCircle(Beta::Mesh* mesh, SpriteSource* spriteSource) {
        GameObject* circle = new GameObject("Circle");

        circle->AddComponent<Sprite>(spriteSource, mesh);
        circle->AddComponent<RigidBody>();
        circle->AddComponent<CircleCollider>();
        circle->AddComponent<ColorChange>(Beta::Colors::Yellow, Beta::Colors::Red);
        circle->AddComponent<ScreenWrap>();

        return circle;
    }

    // Create the point game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    //   spriteSource = The sprite source to use for the object.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreatePoint(Beta::Mesh* mesh, SpriteSource* spriteSource) {
        GameObject* point = new GameObject("Point");

        point->transform()->SetScale(Beta::Vector2D(0.1f, 0.1f));

        point->AddComponent<Sprite>(spriteSource, mesh);
        point->AddComponent<RigidBody>();
        point->AddComponent<PointCollider>();
        point->AddComponent<ColorChange>(Beta::Colors::Blue, Beta::Colors::Red);
        point->AddComponent<ScreenWrap>();

        return point;
    }

    // Create the rectangle game object.
    // Params:
    //   mesh  = The mesh to use for the object's sprite.
    // Returns:
    //	 A pointer to the newly constructed game object
    GameObject* CreateRectangle(Beta::Mesh* mesh) {
        GameObject* rect = new GameObject("Rectangle");

        rect->transform()->SetScale(Beta::Vector2D(2.5f, 1.0f));

        rect->AddComponent<Sprite>(nullptr, mesh);
        rect->AddComponent<RigidBody>();
        rect->AddComponent<BoxCollider>();
        rect->AddComponent<ColorChange>(Beta::Colors::Green, Beta::Colors::Red);
        rect->AddComponent<ScreenWrap>();

        return rect;

    }

    // Create a tilemap object
    // Params:
    //   mesh = The mesh to use for the sprite.
    //   spriteSource = The sprite source to use for the sprite.
    //   map = The map to use for tilemap related components.
    // Returns:
    //   A pointer to the newly constructed game object.
    GameObject* CreateTilemapObject(Beta::Mesh* mesh, SpriteSource* spriteSource, Tilemap* map) {

        GameObject* tmap = new GameObject("tilemap");

        tmap->transform()->SetTranslation(Beta::Vector2D(-3.5f, 2.5f));
        tmap->transform()->SetScale(Beta::Vector2D(1.0f, 1.0f));
        //tmap->transform()->SetScale(Beta::Vector2D(0.25f, 0.25f));

        tmap->AddComponent<SpriteTilemap>(mesh, spriteSource, map);
        tmap->AddComponent<ColliderTilemap>();
        tmap->GetComponent<ColliderTilemap>()->SetTilemap(map);

        return tmap;

    }

}