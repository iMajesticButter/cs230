//------------------------------------------------------------------------------
//
// File Name:	PolygonCollider.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PolygonCollider.h"
#include "Transform.h"
#include "Polygon.h"
#include <DebugDraw.h>
#include "Intersection2D.h"
#include <Shapes2D.h>
#include "CircleCollider.h"
#include "PointCollider.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Allocate a new collider component.
PolygonCollider::PolygonCollider() : Collider(ColliderType::ColliderTypePolygon), m_oldMatrix(CS230::Matrix2D::IdentityMatrix()) {
    //SetColliderVerts();
}

//this class is abstract
PolygonCollider::~PolygonCollider() {
};

// Draw collision shape
void PolygonCollider::Draw() {
    TransformVerts();
#ifdef _DEBUG

    Beta::DebugDraw* debug = EngineGetModule(Beta::DebugDraw);

    for (int i = 0; i < m_transformedVerts.Size(); ++i) {
        Beta::Vector2D& next = (int)i + 1 < m_transformedVerts.Size() ? m_transformedVerts[(int)i + 1] : m_transformedVerts[0];

        debug->AddLineToList(m_transformedVerts[i], next, Beta::Colors::Orange);

    }

    debug->EndLineList();

    Beta::Vector2D tl = m_aabb.center + Beta::Vector2D(+m_aabb.extents.x, +m_aabb.extents.y);
    Beta::Vector2D tr = m_aabb.center + Beta::Vector2D(+m_aabb.extents.x, -m_aabb.extents.y);
    Beta::Vector2D bl = m_aabb.center + Beta::Vector2D(-m_aabb.extents.x, +m_aabb.extents.y);
    Beta::Vector2D br = m_aabb.center + Beta::Vector2D(-m_aabb.extents.x, -m_aabb.extents.y);

    debug->AddLineToList(tl, tr, Beta::Colors::Violet);
    debug->AddLineToList(tr, br, Beta::Colors::Violet);
    debug->AddLineToList(br, bl, Beta::Colors::Violet);
    debug->AddLineToList(bl, tl, Beta::Colors::Violet);
    debug->EndLineList();
#endif
}

// Perform intersection test between two arbitrary colliders.
// Params:
//	 other = Reference to the second collider component.
bool PolygonCollider::IsCollidingWith(const Collider& other) const {
    TransformVerts();

    PolygonColliderInfo poly;
    poly.polyverts = &m_transformedVerts;
    
    switch (other.GetColliderType()) {
        case ColliderType::ColliderTypePoint:
        {

            PointCollider* otherPoint = (PointCollider*)&other;

            return PointPolygonIntersection(other.transform()->GetTranslation() + otherPoint->GetOffset(), poly, m_intersectVector);
        }
        case ColliderType::ColliderTypeCircle:
        {

            CircleCollider* otherC = (CircleCollider*)&other;

            Beta::Circle circle;
            circle.center = other.transform()->GetTranslation() + otherC->GetOffset();
            circle.radius = otherC->GetRadius();

            return PolygonCircleIntersection(poly, circle, m_intersectVector);
        }
        case ColliderType::ColliderTypePolygon:
        {

            PolygonCollider* otherPoly = ((PolygonCollider*)&other);

            otherPoly->TransformVerts();

            PolygonColliderInfo otherPolyInfo;
            otherPolyInfo.polyverts = &otherPoly->m_transformedVerts;

            Beta::Vector2D secondIntersectVector(0, 0);

            if (PolygonPolygonIntersection(poly, otherPolyInfo, m_intersectVector) &&
                PolygonPolygonIntersection(otherPolyInfo, poly, secondIntersectVector)) {

                if (secondIntersectVector.MagnitudeSquared() < m_intersectVector.MagnitudeSquared()) {
                    m_intersectVector = -secondIntersectVector;
                }

                return true;
            }
            m_intersectVector = Beta::Vector2D(0, 0);
        }
        default:
            break;
    }

    return false;
}

// get a pointer to the array of transformed verts
Beta::Data::Vector<Beta::Vector2D>* PolygonCollider::GetTransformedVerts() {
    TransformVerts();
    return &m_transformedVerts;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// check if the transform matrx has changed, if it has, update m_transformedVerts and the aabb
void PolygonCollider::TransformVerts() const {
    const CS230::Matrix2D& matrix = transform()->GetMatrix();
    if (matrix != m_oldMatrix || m_transformedVerts.Size() == 0) {
        //re-calculate the transformed verts and the aabb
        m_oldMatrix = matrix;
        Beta::Vector2D center(0,0);

        m_transformedVerts.Clear();
        for (int i = 0; i < m_verts.Size(); ++i) {
            //transform vertex
            Beta::Vector2D transformed = matrix * m_verts[i];
            m_transformedVerts.push_back(transformed);
            
            //aabb stuff
            center += transformed;

        }

        //calculate bounding box extents
        center /= (float)m_verts.Size();

        Beta::Vector2D extents(0, 0);

        for (int i = 0; i < m_transformedVerts.Size(); ++i) {
            float xDist = std::abs(center.x - m_transformedVerts[i].x);
            float yDist = std::abs(center.y - m_transformedVerts[i].y);
            if (xDist > extents.x) {
                extents.x = xDist;
            }
            if (yDist > extents.y) {
                extents.y = yDist;
            }
        }

        m_aabb = Beta::BoundingRectangle(center, extents);

    }
}

// Get an axis-aligned-bounding-box for this collider (used for tilemap collisions)
Beta::BoundingRectangle PolygonCollider::GetAABB() {
    return m_aabb;
}

COMPONENT_ABSTRACT_SUBCLASS_DEFINITIONS(Collider, PolygonCollider)