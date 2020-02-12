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
#include "Matrix2DStudent.h"

class PolygonCollider : public Collider {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Allocate a new collider component.
    PolygonCollider();

    //this class is abstract
    virtual ~PolygonCollider() = 0;

    // Set up collider verts
    //virtual void SetColliderVerts() = 0;

    // Draw collision shape
    virtual void Draw() override;

    // Perform intersection test between two arbitrary colliders.
    // Params:
    //	 other = Reference to the second collider component.
    virtual bool IsCollidingWith(const Collider& other) const override;

    // get a pointer to the array of transformed verts
    Beta::Data::Vector<Beta::Vector2D>* GetTransformedVerts();

    // Get an axis-aligned-bounding-box for this collider (used for tilemap collisions)
    virtual Beta::BoundingRectangle GetAABB();


private:

    // check if the transform matrx has changed, if it has, update m_transformedVerts
    void TransformVerts() const;

    // a copy of the transform matrix to compare against
    mutable CS230::Matrix2D m_oldMatrix;

    //vertecies
    mutable Beta::Data::Vector<Beta::Vector2D> m_transformedVerts;

    //axis-aligned-bounding-box
    mutable Beta::BoundingRectangle m_aabb;

protected: 
    Beta::Data::Vector<Beta::Vector2D> m_verts;

    COMPONENT_ABSTRACT_SUBCLASS_DECLARATIONS(PolygonCollider)

};