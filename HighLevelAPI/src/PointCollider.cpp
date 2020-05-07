//------------------------------------------------------------------------------
//
// File Name:	PointCollider.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PointCollider.h"

#include "Transform.h"
#include "PolygonCollider.h"
#include "CircleCollider.h"
#include "Intersection2D.h"
#include "Polygon.h"
#include <Shapes2D.h>

//default constructor
PointCollider::PointCollider(Beta::Vector2D offset) : Collider(ColliderType::ColliderTypePoint), m_offset(offset) {
    
}

// Draw collision shape
void PointCollider::Draw() {
#ifdef _DEBUG
    auto debug = EngineGetModule(Beta::DebugDraw);
    debug->AddCircle(transform()->GetTranslation() + GetOffset(), 0.05f, Beta::Colors::Orange);


    Beta::BoundingRectangle aabb = GetAABB();

    Beta::Vector2D tl = aabb.center + Beta::Vector2D(+aabb.extents.x, +aabb.extents.y);
    Beta::Vector2D tr = aabb.center + Beta::Vector2D(+aabb.extents.x, -aabb.extents.y);
    Beta::Vector2D bl = aabb.center + Beta::Vector2D(-aabb.extents.x, +aabb.extents.y);
    Beta::Vector2D br = aabb.center + Beta::Vector2D(-aabb.extents.x, -aabb.extents.y);

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
bool PointCollider::IsCollidingWith(const Collider& other) const {

    Beta::Vector2D myPos = transform()->GetTranslation() + GetOffset();

    switch (other.GetColliderType()) {
        case ColliderType::ColliderTypeCircle:
        {

            CircleCollider* otherC = (CircleCollider*)&other;

            Beta::Circle circle;
            circle.center = otherC->transform()->GetTranslation() + otherC->GetOffset();
            circle.radius = otherC->GetRadius();

            return PointCircleIntersection(myPos, circle, m_intersectVector);
        }
        case ColliderType::ColliderTypePolygon:
        case ColliderType::ColliderTypeTilemap:
        {
            bool colliding = other.IsCollidingWith(*this);
            m_intersectVector = -other.GetIntersectVector();
            return colliding;
        }
        case ColliderType::ColliderTypePoint:
        default:
            break;
    }
    return false;
}

//set the colliders offset
void PointCollider::SetOffset(Beta::Vector2D offset) {
    m_offset = offset;
}

//get the colliders offset
Beta::Vector2D PointCollider::GetOffset() const {
    return Beta::Vector2D(transform()->GetScale().x * m_offset.x, transform()->GetScale().y * m_offset.y);
}

// Get an axis-aligned-bounding-box for this collider (used for tilemap collisions)
Beta::BoundingRectangle PointCollider::GetAABB() const {
    return Beta::BoundingRectangle(transform()->GetTranslation() + GetOffset(), Beta::Vector2D(0, 0));
}


COMPONENT_SUBCLASS_DEFINITIONS(Collider, PointCollider)