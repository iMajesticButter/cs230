//------------------------------------------------------------------------------
//
// File Name:	GameObject.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>
#include "betaVector.h"
#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Component;
class Space;
class Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class GameObject : public Beta::BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new game object.
	// Params:
	//	 name = The name of the game object being created.
    //   hasTransform = Wheather the object should have a transform component (defaults to true)
	GameObject(const std::string& name, bool hasTransform = true);

	// Clone a game object from another game object.
	// Params:
	//	 other = A reference to the object being cloned.
	GameObject(const GameObject& other);

	// Free the memory associated with a game object.
	~GameObject();

	// Initialize this object's components and set it to active.
	void Initialize() override;

	// Update any components attached to the game object.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Updates components using a fixed timestep (usually just physics)
	// Params:
	//	 dt = A fixed change in time, usually 1/60th of a second.
	void FixedUpdate(float dt) override;

	// Draw any visible components attached to the game object.
	void Draw() override;
	
	// Adds a component to the object.
	void AddComponent(Component* component);

    // Adds a component to the object.
    template <class C, typename... params>
    C* AddComponent(params...);

    // Removes a component from the object
    template <class C>
    void RemoveComponent();

	// Retrieves the component with the given name if it exists.
	// Params:
	//   name = The name of the component to find.
	Component* GetComponent(const std::string& name);

    // Retrieves the component with the given type if it exists
    template <class C>
    C* GetComponent();
	
	// Mark an object for destruction.
	void Destroy();
	
	// Whether the object has been marked for destruction.
	// Returns:
	//		True if the object will be destroyed, false otherwise.
	bool IsDestroyed() const;

	// Get the space that contains this object.
	Space* GetSpace() const;

    // Get the objects transform component if it exists (it does by default)
    Transform* transform();

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Components
    Beta::Data::Vector<Component*> m_components;
	//unsigned numComponents;

	// Whether the object has been marked for destruction.
	bool isDestroyed;

    // A ponter to the objects transform component
    Transform* m_transform;
};

#define GAMEOBJECT_HEADER

#include "ComponentGameObjectTemplateFunctions.h"

//------------------------------------------------------------------------------
