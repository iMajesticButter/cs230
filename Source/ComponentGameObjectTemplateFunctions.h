//------------------------------------------------------------------------------
//
// File Name:	ComponentGameObjectTemplateFunctions.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


// this file is here to get around circular dependencies with templated member functions
// the documentaion on these functions is in their respective class declarations


#include "Component.h"
#include "GameObject.h"



#ifndef GAMEOBJECT_TEMPLATED_FUNCS

#ifdef GAMEOBJECT_HEADER

#define GAMEOBJECT_TEMPLATED_FUNCS

//templated functions

template <class C>
C* GameObject::GetComponent() {
    for (int i = 0; i < m_components.Size(); ++i) {
        if (C::ComponentType == m_components[i]->GetType()) {
            return (C*)m_components[i];
        }
    }
    return nullptr;
}

template <class C>
void GameObject::RemoveComponent() {
    if (C::ComponentType == Transform::ComponentType) {
        m_transform = nullptr;
    }
    for (int i = 0; i < m_components.Size(); ++i) {
        if (C::ComponentType == m_components[i]->GetType()) {
            m_components.remove(i);
            return;
        }
    }
}

// Adds a component to the object.
template <class C, typename... params>
C* GameObject::AddComponent(params... parameters) {
    C* component = new C(parameters...);
    AddComponent(component);
    return component;
}

#endif
#endif

#ifndef COMPONENT_TEMPLATED_FUNCS

#ifdef GAMEOBJECT_HEADER
#ifdef COMPONENT_HEADER
#define COMPONENT_TEMPLATED_FUNCS

template <class C>
C* Component::GetComponent() {
    return GetOwner()->GetComponent<C>();
}
#endif
#endif

#endif
