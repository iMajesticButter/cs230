//------------------------------------------------------------------------------
//
// File Name:	PointCollider.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Collider.h"

class PointCollider : public Collider {
public:

    //default constructor
    PointCollider(Beta::Vector2D offset = Beta::Vector2D(0, 0));

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

    // Get an axis-aligned-bounding-box for this collider (used for tilemap collisions)
    virtual Beta::BoundingRectangle GetAABB();

private:

    Beta::Vector2D m_offset;

    COMPONENT_SUBCLASS_DECLARATIONS(CircleCollider)

};

