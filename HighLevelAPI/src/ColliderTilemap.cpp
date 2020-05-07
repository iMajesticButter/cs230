//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ColliderTilemap.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Tilemap.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor for Tilemap collider.
ColliderTilemap::ColliderTilemap() : Collider(ColliderType::ColliderTypeTilemap), m_map(nullptr) {
    Collider::SetTriggerOnly(true);
}

// Debug drawing for colliders.
void ColliderTilemap::Draw() {
#ifdef _DEBUG

    auto debug = EngineGetModule(Beta::DebugDraw);

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

// Check for collision between a tilemap and another arbitrary collider.
// Params:
//	 other = Reference to the second collider component.
// Returns:
//	 Return the results of the collision check.
bool ColliderTilemap::IsCollidingWith(const Collider& other) const {

    Beta::BoundingRectangle rect = other.GetAABB();

    bool leftCol = IsSideColliding(rect, RectangleSide::SideLeft);
    bool rightCol = IsSideColliding(rect, RectangleSide::SideRight);
    bool topCol = IsSideColliding(rect, RectangleSide::SideTop);
    bool bottomCol = IsSideColliding(rect, RectangleSide::SideBottom);

    auto rb = other.GetOwner()->GetComponent<RigidBody>();
    Beta::Vector2D oldTranslation = rb->GetOldTranslation();

    if (topCol || bottomCol) {
        other.transform()->SetTranslation(Beta::Vector2D(other.transform()->GetTranslation().x, oldTranslation.y));
        rb->SetVelocity(Beta::Vector2D(rb->GetVelocity().x, 0));
    }

    if (leftCol || rightCol) {
        other.transform()->SetTranslation(Beta::Vector2D(oldTranslation.x, other.transform()->GetTranslation().y));
        rb->SetVelocity(Beta::Vector2D(0, rb->GetVelocity().y));
    }

    //calculate intersect vector
    float intersectX = 0;
    float intersectY = 0;

    if (leftCol) {
        ++intersectX;
    }
    if (rightCol) {
        --intersectX;
    }
    if (topCol) {
        --intersectY;
    }
    if (bottomCol) {
        ++intersectY;
    }

    m_intersectVector = Beta::Vector2D(intersectX, intersectY) * 0.1f;
    return leftCol || rightCol || topCol || bottomCol;
}

// Sets the tilemap to use for this collider.
// Params:
//   map = A pointer to the tilemap resource.
void ColliderTilemap::SetTilemap(const Tilemap* map) {
    m_map = map;
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Checks whether the specified side of a given rectangle is colliding with the tilemap.
// Params:
//   rectangle = The bounding rectangle for an object.
//   side = The side that needs to be tested for collision.
// Returns:
//   True if there is a collision, false otherwise.
bool ColliderTilemap::IsSideColliding(const Beta::BoundingRectangle& rectangle, RectangleSide side) const {
    
    Beta::Vector2D spot1;
    Beta::Vector2D spot2;

    //how far along the edges are the hotspots
    const float hotspotPosition = 0.75f;

    switch (side) {
        case RectangleSide::SideBottom:
            spot1 = Beta::Vector2D(rectangle.center.x + rectangle.extents.x * hotspotPosition, rectangle.bottom);
            spot2 = Beta::Vector2D(rectangle.center.x - rectangle.extents.x * hotspotPosition, rectangle.bottom);
            break;
        case RectangleSide::SideTop:
            spot1 = Beta::Vector2D(rectangle.center.x + rectangle.extents.x * hotspotPosition, rectangle.top);
            spot2 = Beta::Vector2D(rectangle.center.x - rectangle.extents.x * hotspotPosition, rectangle.top);
            break;
        case RectangleSide::SideLeft:
            spot1 = Beta::Vector2D(rectangle.left, rectangle.center.y + rectangle.extents.y * hotspotPosition);
            spot2 = Beta::Vector2D(rectangle.left, rectangle.center.y - rectangle.extents.y * hotspotPosition);
            break;
        case RectangleSide::SideRight:
            spot1 = Beta::Vector2D(rectangle.right, rectangle.center.y + rectangle.extents.y * hotspotPosition);
            spot2 = Beta::Vector2D(rectangle.right, rectangle.center.y - rectangle.extents.y * hotspotPosition);
            break;
        default:
            break;
    }

#ifdef _DEBUG
    //debug draw the hotspots

    auto debug = EngineGetModule(Beta::DebugDraw);

    debug->AddCircle(spot1, 0.025f, Beta::Colors::Red);
    debug->AddCircle(spot2, 0.025f, Beta::Colors::Red);

#endif

    if (IsCollidingAtPosition(spot1.x, spot1.y) || IsCollidingAtPosition(spot2.x, spot2.y)) {
        return true;
    }
    return false;
}

// Determines whether a point is within a collidable cell in the tilemap.
// Params:
//   x = The x component of the point, in world coordinates.
//   y = The y component of the point, in world coordinates.
// Returns:
//   False if the point is outside the map or the map is empty at that position, 
//   or true if there is a tile at that position.
bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const {
    Beta::Vector2D pos(x, y);

    pos = transform()->GetInverseMatrix() * pos;

    pos = Beta::Vector2D(pos.x + 0.5f, -pos.y + 0.5f);

    int newX = (int)pos.x;
    int newY = (int)pos.y;

    return m_map->GetCellValue(newX, newY) > 0;
}

// Moves an object and sets its velocity based on where it collided with the tilemap.
// Params:
//   objectRectangle = A bounding rectangle that encompasses the object.
//   objectTransform = Pointer to the object's transform component.
//   objectRigidBody = Pointer to the object's rigidBody component.
//   collisions = True/false values from map collision checks.
void ColliderTilemap::ResolveCollisions(const Beta::BoundingRectangle& objectRectangle, Transform* objectTransform,
                                        RigidBody* objectRigidBody, const MapCollision& collisions) const {
    UNREFERENCED_PARAMETER(objectRectangle);
    UNREFERENCED_PARAMETER(objectTransform);
    UNREFERENCED_PARAMETER(objectRigidBody);
    UNREFERENCED_PARAMETER(collisions);
}

// Returns the center of the next tile on the x-axis or y-axis.
// Used for assisting in collision resolution on a particular side.
// Params:
//   side = Which side the collision is occurring on.
//   sidePosition = The x or y value of that side.
// Returns:
//   The center of the next tile for the given position on the given side.
float ColliderTilemap::GetNextTileCenter(RectangleSide side, float sidePosition) const {
    UNREFERENCED_PARAMETER(side);
    UNREFERENCED_PARAMETER(sidePosition);
    return 0.0f;
}

// Get the colliders aabb
Beta::BoundingRectangle ColliderTilemap::GetAABB() const {
    
    Beta::Vector2D extents = Beta::Vector2D((m_map->GetWidth()  / 2) * transform()->GetScale().x,
                                            (m_map->GetHeight() / 2) * transform()->GetScale().y);

    Beta::Vector2D center = transform()->GetTranslation() + 
        Beta::Vector2D(extents.x - transform()->GetScale().x/2, -extents.y + transform()->GetScale().y / 2);

    Beta::BoundingRectangle rect(center, extents);

    return rect;
}

COMPONENT_SUBCLASS_DEFINITIONS(Collider, ColliderTilemap)