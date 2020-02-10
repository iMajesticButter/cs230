//------------------------------------------------------------------------------
//
// File Name:	CircleCollider.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "CircleCollider.h"
#include "Transform.h"
#include "Intersection2D.h"
#include <Shapes2D.h>
#include "Polygon.h"
#include "PolygonCollider.h"
#include "PointCollider.h"

//default constructor
CircleCollider::CircleCollider(float radius, Beta::Vector2D offset) : Collider(ColliderType::ColliderTypeCircle),
m_offset(offset), m_radius(radius) {
}

// Draw collision shape
void CircleCollider::Draw() {
    auto debug = EngineGetModule(Beta::DebugDraw);

    debug->AddCircle(transform()->GetTranslation() + GetOffset(), GetRadius(), Beta::Colors::Orange);
}

// Perform intersection test between two arbitrary colliders.
// Params:
//	 other = Reference to the second collider component.
bool CircleCollider::IsCollidingWith(const Collider& other) const {

    Beta::Circle circle1;
    circle1.center = transform()->GetTranslation() + GetOffset();
    circle1.radius = GetRadius();

    switch (other.GetColliderType()) {
        case ColliderType::ColliderTypeCircle:
        {

            CircleCollider* otherC = (CircleCollider*)&other;

            Beta::Circle circle2;
            circle2.center = other.transform()->GetTranslation() + otherC->GetOffset();
            circle2.radius = otherC->GetRadius();

            return CircleCircleIntersection(circle1, circle2, m_intersectVector);

        }
        case ColliderType::ColliderTypePoint:
        {
            PointCollider* otherP = (PointCollider*)&other;

            bool intersectPoint = PointCircleIntersection(other.transform()->GetTranslation() + otherP->GetOffset(), circle1, m_intersectVector);

            m_intersectVector = -m_intersectVector;
            return intersectPoint;

        }
        case ColliderType::ColliderTypePolygon:
        {

            PolygonCollider* otherPoly = (PolygonCollider*)&other;

            PolygonColliderInfo otherInfo;
            otherInfo.polyverts = otherPoly->GetTransformedVerts();

            bool intersectPoly = PolygonCircleIntersection(otherInfo, circle1, m_intersectVector);

            m_intersectVector = -m_intersectVector;

            return intersectPoly;
            break;
        }
        default:
            break;
    }

    return false;
}

//set the colliders offset
void CircleCollider::SetOffset(Beta::Vector2D offset) {
    m_offset = offset;
}

//get the colliders offset
Beta::Vector2D CircleCollider::GetOffset() const {
    return Beta::Vector2D(transform()->GetScale().x * m_offset.x, transform()->GetScale().y * m_offset.y);
}

//set the colliders radius
void CircleCollider::SetRadius(float radius) {
    m_radius = radius;
}

//get the colliders radius
float CircleCollider::GetRadius() const {
    return m_radius * std::min(transform()->GetScale().x, transform()->GetScale().y);
}

COMPONENT_SUBCLASS_DEFINITIONS(Collider, CircleCollider)