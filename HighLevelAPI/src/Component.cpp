//------------------------------------------------------------------------------
//
// File Name:	Component.cpp
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020 
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor - needed to construct BetaObject.
Component::Component(const std::string& name) : Beta::BetaObject(name) {

}

// Retrieve component's owner object (if any).
GameObject* Component::GetOwner() const {
    return (GameObject*)BetaObject::GetOwner();
}

// Retrieves the component with the given name on the owner object if it exists.
// Params:
//   name = The name of the component to find.
Component* Component::GetComponent(const std::string& componentName) {
    return GetOwner()->GetComponent(componentName);
}

// Get the owner objects transform component if it exists (it does by default)
Transform* Component::transform() const {
    return GetOwner()->transform();
}

// Get the space that the owner object belongs to
Space* Component::GetSpace() const {
    return GetOwner()->GetSpace();
}