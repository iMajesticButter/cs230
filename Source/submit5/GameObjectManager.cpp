//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.cpp
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "GameObjectManager.h"
#include "Space.h"
#include "GameObject.h"
#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
GameObjectManager::GameObjectManager(Space* space) : Beta::BetaObject("ObjectManager", (BetaObject*)space), m_fixedUpdateDt(1.0f/60.0f), m_timeAccumulator(0) {
    
}

// Destructor
GameObjectManager::~GameObjectManager() {
    Shutdown();
    Unload();
}

// Get this object managers space
Space* GameObjectManager::GetSpace() {
    return (Space*)BetaObject::GetOwner();
}

// Update all objects in the active game objects list.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManager::Update(float dt) {
    if (GetSpace()->IsPaused()) {
        //this is a better way to pause because you can still run scripts to un-pause and run the ui (unity pauses like this)
        dt = 0;
    }

    VariableUpdate(dt);
    FixedUpdate(dt);

    DestroyObjects();
    Draw();

}

// Shutdown the game object manager, destroying all active objects.
void GameObjectManager::Shutdown(void) {
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        delete m_activeObjects[i];
    }
    m_activeObjects.Clear();
}

// Unload the game object manager, destroying all object archetypes.
void GameObjectManager::Unload(void) {
    for (int i = 0; i < m_archetypes.Size(); ++i) {
        delete m_archetypes[i];
    }
    m_archetypes.Clear();
}

// Add a game object to the active game object list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddObject(GameObject& gameObject) {
    gameObject.SetOwner(GetOwner());
    gameObject.Initialize();
    m_activeObjects.push_back(&gameObject);
}

// Add a game object to the game object archetype list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddArchetype(GameObject& gameObject) {
    m_archetypes.push_back(&gameObject);
}

// Returns a pointer to the first active game object matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   If the named object is found,
//	   then return the pointer to the named game object,
//	   else return nullptr.
GameObject* GameObjectManager::GetObjectByName(const std::string& objectName) const {
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        if (m_activeObjects[i]->GetName() == objectName) {
            return m_activeObjects[i];
        }
    }
    return nullptr;
}

// Returns a list of all active game object matching the specified name.
// Params:
//	 objectName = The name of the objects to be returned, if found.
// Returns:
//   A list of all objects with the specified name
Beta::Data::Vector<GameObject*> GameObjectManager::GetObjectsByName(const std::string& objectName) const {
    Beta::Data::Vector<GameObject*> objects;
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        if (m_activeObjects[i]->GetName() == objectName) {
            objects.push_back(m_activeObjects[i]);
        }
    }
    return objects;
}

// Returns a pointer to the first game object archetype matching the specified name.
// Params:
//	 objectName = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return nullptr.
GameObject* GameObjectManager::GetArchetypeByName(const std::string& objectName) const {
    for (int i = 0; i < m_archetypes.Size(); ++i) {
        if (m_archetypes[i]->GetName() == objectName) {
            return m_archetypes[i];
        }
    }
    return nullptr;
}

// Returns the number of active objects with the given name.
// Params:
//   objectName = The name of the objects that should be counted.
unsigned GameObjectManager::GetObjectCount(const std::string& objectName) const {
    unsigned count = 0;
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        if (m_activeObjects[i]->GetName() == objectName) {
            ++count;
        }
    }
    return count;
}



//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------


// Update object logic using variable timestep.
void GameObjectManager::VariableUpdate(float dt) {
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        m_activeObjects[i]->Update(dt);
    }
}

// Update object physics using fixed timestep.
void GameObjectManager::FixedUpdate(float dt) {
    m_timeAccumulator += dt;
    while (m_timeAccumulator >= m_fixedUpdateDt) {
        m_timeAccumulator -= m_fixedUpdateDt;
        for (int i = 0; i < m_activeObjects.Size(); ++i) {
            m_activeObjects[i]->FixedUpdate(m_fixedUpdateDt);
        }
        CheckCollisions();
    }
}

// Destroy any objects marked for destruction.
void GameObjectManager::DestroyObjects() {
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        //std::cout << i << ", " << m_activeObjects.Size() << std::endl;
        if (m_activeObjects[i]->IsDestroyed()) {

            delete m_activeObjects[i];
            m_activeObjects.remove(i);

            --i;
        }
    }
}

// Draw all game objects in the active game object list.
void GameObjectManager::Draw(void) {
    for (int i = 0; i < m_activeObjects.Size(); ++i) {
        m_activeObjects[i]->Draw();
    }
}

// Check collision between all objects
void GameObjectManager::CheckCollisions() {

    for (int i = 0; i < m_activeObjects.Size()-1; ++i) {
        if (m_activeObjects[i]->IsDestroyed())
            continue;

        Collider* obj1Col = m_activeObjects[i]->GetComponent<Collider>();
        if (obj1Col == nullptr)
            continue;

        std::cout << "check collision object: " << i << std::endl;

        for (int j = i + 1; j < m_activeObjects.Size(); ++j) {
            if (m_activeObjects[j]->IsDestroyed())
                continue;

            Collider* obj2Col = m_activeObjects[j]->GetComponent<Collider>();
            if (obj2Col == nullptr)
                continue;

            std::cout << "and: " << j << std::endl;

            Beta::Vector2D intersectVector = obj1Col->CheckCollision(*obj2Col);
            
            if (intersectVector.Magnitude() == 0) {
                //no collision, return
                continue;
            }

            // Resolve the collision
            if (obj1Col->GetTriggerOnly() || obj2Col->GetTriggerOnly()) {
                //one or more of the colliders are trigger-only, return
                continue;
            }

            GameObject* obj1 = obj1Col->GetOwner();
            GameObject* obj2 = obj2Col->GetOwner();

            auto rb = obj1->GetComponent<RigidBody>();
            auto rb2 = obj2->GetComponent<RigidBody>();

            if (rb == nullptr && rb2 == nullptr) {
                // Both objects are static, return
                continue;
            }

            float obj1Vel = 0;
            float obj1Mass = 10;
            if (rb != nullptr) {
                obj1Vel = rb->GetVelocity().DotProduct(intersectVector);
                obj1Mass = rb->GetMass();
            }

            float obj2Vel = 0;
            float obj2Mass = 10;
            if (rb2 != nullptr) {
                obj2Vel = rb2->GetVelocity().DotProduct(intersectVector);
                obj2Mass = rb2->GetMass();
            }

            //move the object(s) so that there is no longer an intersection
            if (rb != nullptr && rb2 != nullptr) {
                if (obj2Mass > obj1Mass) {
                    obj1->transform()->SetTranslation(obj1->transform()->GetTranslation() - intersectVector);
                } else {
                    obj2->transform()->SetTranslation(obj2->transform()->GetTranslation() + intersectVector);
                }
            } else if (rb != nullptr) {
                obj1->transform()->SetTranslation(obj1->transform()->GetTranslation() - intersectVector);
            } else {
                obj2->transform()->SetTranslation(obj2->transform()->GetTranslation() + intersectVector);
            }

            //calculate final velocity along the intersect vector
            //float massesSum = obj1Mass + obj2Mass;
            float momentum = (obj1Mass * obj1Vel) + (obj2Mass + obj2Vel);

            //float velocity = momentum / massesSum;

            float v1 = (momentum - (obj2Mass * obj2Vel)) / obj1Mass;
            float v2 = (momentum - (obj1Mass * obj1Vel)) / obj2Mass;

            //apply this velocity along the intersect vector to the objects
            if (rb != nullptr) {
                rb->SetVelocity(rb->GetVelocity() - ((obj1Vel + v1) * intersectVector.Normalized()));
            }
            if (rb2 != nullptr) {
                rb2->SetVelocity(rb2->GetVelocity() + ((obj2Vel + v2) * intersectVector.Normalized()));
            }

        }
    }

}