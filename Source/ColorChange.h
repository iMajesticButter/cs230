//------------------------------------------------------------------------------
//
// File Name:	ColorChange.h
// Author(s):	Brandon Wolenetz
// Project:		lab6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class
#include <Color.h>	// Color

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Sprite;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColorChange : public Component {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Constructor
    // Params:
    //   normalColor = The color that the object reverts to when not colliding.
    //   collidedColor = The color that the object changes to when colliding.
    //   collidedColorTime = The amount of time the object will retain the collided color.
    ColorChange(const Beta::Color& normalColor, const Beta::Color& collidedColor, float collidedColorTime = 0.1f);

    // Initialize data for this object.
    void Initialize();

    // Update function for this component.
    // Params:
    //   dt = The (fixed) change in time since the last step.
    void Update(float dt) override;

    // Collision handler for ColorChange objects.
    // Params:
    //   object = The first object.
    //   other  = The other object the first object is colliding with.
    friend void ColorChangeCollisionHandler(GameObject& object, GameObject& other, Beta::Vector2D intersectVector);

private:
    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // Components
    Sprite* m_sprite;

    // Properties
    Beta::Color m_normalColor;
    Beta::Color m_collidedColor;
    float m_collidedColorTime;

    // Other variables
    bool m_collided;
    float m_timer;

    COMPONENT_CLASS_DECLARATIONS(ColorChange)
};
