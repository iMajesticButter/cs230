//------------------------------------------------------------------------------
//
// File Name:	PolygonCollider.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Collider.h"

class PolygonCollider : public Collider {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Allocate a new collider component.
    PolygonCollider();

    // Set up collider verts
    virtual void SetColliderVerts() = 0;

    // Draw collision shape
    virtual void Draw() override;

    // Perform intersection test between two arbitrary colliders.
    // Params:
    //	 other = Reference to the second collider component.
    virtual bool IsCollidingWith(const Collider& other) const override;


private:

    //vertecies
    Beta::Data::Vector<Beta::Vector2D> m_verts;
    Beta::Data::Vector<Beta::Vector2D> m_transformedVerts;

};