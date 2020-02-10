//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "GameObject.h"
#include "Transform.h"


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new game object.
// Params:
//	 name = The name of the game object being created.
//   hasTransform = Wheather the object should have a transform component (defaults to true)
GameObject::GameObject(const std::string& name, bool hasTransform) : Beta::BetaObject(name), m_transform(nullptr), isDestroyed(false) {
    if (hasTransform) {
        m_transform = new Transform();
        m_components.push_back(m_transform);
    }
}

// Clone a game object from another game object.
// Params:
//	 other = A reference to the object being cloned.
GameObject::GameObject(const GameObject& other) : Beta::BetaObject(other.GetName()), m_transform(nullptr), isDestroyed(false) {
    for (int i = 0; i < other.m_components.Size(); ++i) {
        Component* component = other.m_components[i]->Clone();
        component->SetOwner(this);
        m_components.push_back(component);
    }
}

// Free the memory associated with a game object.
GameObject::~GameObject() {
    for (int i = 0; i < m_components.Size(); ++i) {
        delete m_components[i];
    }
}

// Initialize this object's components and set it to active.
void GameObject::Initialize() {
    for (int i = 0; i < m_components.Size(); ++i) {
        m_components[i]->Initialize();
    }
}

// Update any components attached to the game object.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObject::Update(float dt) {
    if (isDestroyed)
        return;

    for (int i = 0; i < m_components.Size(); ++i) {
        m_components[i]->Update(dt);
    }
}

// Updates components using a fixed timestep (usually just physics)
// Params:
//	 dt = A fixed change in time, usually 1/60th of a second.
void GameObject::FixedUpdate(float dt) {
    if (isDestroyed)
        return;

    for (int i = 0; i < m_components.Size(); ++i) {
        m_components[i]->FixedUpdate(dt);
    }
}

// Draw any visible components attached to the game object.
void GameObject::Draw() {
    for (int i = 0; i < m_components.Size(); ++i) {
        m_components[i]->Draw();
    }
}

// Adds a component to the object.
void GameObject::AddComponent(Component* component) {
    component->SetOwner(this);
    m_components.push_back(component);
}

// Retrieves the component with the given name if it exists.
// Params:
//   name = The name of the component to find.
Component* GameObject::GetComponent(const std::string& componentName) {
    for (int i = 0; i < m_components.Size(); ++i) {
        if (m_components[i]->GetName() == componentName) {
            return m_components[i];
        }
    }
    return nullptr;
}

// Mark an object for destruction.
void GameObject::Destroy() {
    isDestroyed = true;
}

// Whether the object has been marked for destruction.
// Returns:
//		True if the object will be destroyed, false otherwise.
bool GameObject::IsDestroyed() const {
    return isDestroyed;
}

// Get the space that contains this object.
Space* GameObject::GetSpace() const {
    return (Space*)BetaObject::GetOwner();
}

// Get the objects transform component if it exists (it does by default)
Transform* GameObject::transform() {
    if (m_transform == nullptr) {
        m_transform = GetComponent<Transform>();
    }

    return m_transform;
}