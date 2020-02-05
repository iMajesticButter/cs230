//------------------------------------------------------------------------------
//
// File Name:	Component.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020 
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once


//------------------------------------------------------------------------------
// Component Macros
//------------------------------------------------------------------------------

#define TYPENAME_TO_STRING(x) #x


#define COMPONENT_CLASS_DECLARATIONS(type) public: \
Component* Clone() const; \
size_t GetType() const;\
static size_t ComponentType;

#define COMPONENT_CLASS_DEFINITIONS(type) \
size_t type::ComponentType = std::hash<std::string>{}(TYPENAME_TO_STRING(type));\
\
Component* type::Clone() const {\
 return new type(*this); \
} \
\
size_t type::GetType() const { \
    return type::ComponentType;            \
}


//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
class Transform;
class Space;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface (function prototypes) declared in the header.
class Component : public Beta::BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor - needed to construct BetaObject.
	Component(const std::string& name);

	// Clones the component, returning a dynamically allocated copy.
	virtual Component* Clone() const = 0;

	// Retrieve component's owner object (if any).
	GameObject* GetOwner() const;

    // Retrieve components type hash
    virtual size_t GetType() const = 0;

    // Retrieves the component with the given name on the owner object if it exists.
    // Params:
    //   name = The name of the component to find.
    Component* GetComponent(const std::string& name);

    // Retrieves the component with the given type on the owner object if it exists
    template <class C>
    C* GetComponent();

    // Get the owner objects transform component if it exists (it does by default)
    Transform* transform() const;

    // Get the space that the owner object belongs to
    Space* GetSpace() const;

private:

};

#define COMPONENT_HEADER
#include "ComponentGameObjectTemplateFunctions.h"

//------------------------------------------------------------------------------
