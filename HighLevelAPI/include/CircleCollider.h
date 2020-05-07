//------------------------------------------------------------------------------
//
// File Name:	CircleCollider.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Collider.h"

class CircleCollider : public Collider {
public:

    //default constructor
    CircleCollider(float radius = 0.5f, Beta::Vector2D offset = Beta::Vector2D(0, 0));

    // Draw collision shape
    virtual void Draw() override;

    // Perform intersection test between two arbitrary colliders.
    // Params:
    //	 other = Reference to the second collider component.
    virtual bool IsCollidingWith(const Collider& other) const override;

    //set the colliders offset
    void SetOffset(Beta::Vector2D offset);

    //get the colliders offset
    Beta::Vector2D GetOffset() const;

    //set the colliders radius
    void SetRadius(float radius);

    //get the colliders radius
    float GetRadius() const;

    // Get an axis-aligned-bounding-box for this collider (used for tilemap collisions)
    virtual Beta::BoundingRectangle GetAABB() const;

private:

    Beta::Vector2D m_offset;
    float m_radius;

    COMPONENT_SUBCLASS_DECLARATIONS(CircleCollider)

};
