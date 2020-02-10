//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Shapes2D.h"
#include "betaVector.h"
#include "Polygon.h"


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Transform;
class RigidBody;

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Beta::Vector2D& point, const Beta::Circle& circle, Beta::Vector2D& intersectVector);

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  polygon  = The polygon in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointPolygonIntersection(const Beta::Vector2D& point, PolygonColliderInfo polygon, Beta::Vector2D& intersectVector);

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Beta::Circle& circle1, const Beta::Circle& circle2, Beta::Vector2D& intersectVector);

// Check whether two polygons intersect.
// Params:
//  poly1 = The first polygon.
//	poly2 = The second polygon.
// Returns:
//   True if intersection, false otherwise.
bool PolygonPolygonIntersection(PolygonColliderInfo poly1, PolygonColliderInfo poly2, Beta::Vector2D& intersectVector);

// Check whether a polygon and circle intersect.
// Params:
//  polygon = The polygon.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool PolygonCircleIntersection(PolygonColliderInfo polygon, const Beta::Circle& circle, Beta::Vector2D& intersectVector);

//------------------------------------------------------------------------------
