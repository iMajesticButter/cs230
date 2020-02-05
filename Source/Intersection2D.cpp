//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Intersection2D.h"

using namespace Beta;

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Beta::Vector2D& point, const Beta::Circle& circle, Beta::Vector2D& intersectVector) {

    float dist = point.Distance(circle.center);

    if (dist <= circle.radius) {
        //set the intersect vector
        intersectVector = (point - circle.center).Normalized() * (circle.radius - dist);

        return true;
    }
    return false;
}

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  polygon  = The polygon in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointPolygonIntersection(const Beta::Vector2D& point, PolygonColliderInfo polygon, Beta::Vector2D& intersectVector) {
    bool intersect = PolygonCircleIntersection(polygon, Circle(point, 0), intersectVector);
    intersectVector = -intersectVector;
    return intersect;
}

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Beta::Circle& circle1, const Beta::Circle& circle2, Beta::Vector2D& intersectVector) {
    
    float dist = circle1.center.Distance(circle2.center);
    float combinedRadius = circle1.radius + circle2.radius;

    if (dist <= combinedRadius) {
        //set the intersect vector
        intersectVector = (circle1.center - circle2.center).Normalized() * (combinedRadius - dist);

        return true;
    }
    return false;

}

// Check whether two polygons intersect.
// Params:
//  poly1 = The first polygon.
//	poly2 = The second polygon.
// Returns:
//   True if intersection, false otherwise.
bool PolygonPolygonIntersection(PolygonColliderInfo poly1, PolygonColliderInfo poly2, Beta::Vector2D& intersectVector) {

    //Data::Vector<Vector2D>& p1 = *poly1.polyverts;
    //Data::Vector<Vector2D>& p2 = *poly2.polyverts;

    Data::Vector<Vector2D> p1 = *poly1.polyverts;
    Data::Vector<Vector2D> p2 = *poly2.polyverts;

    //TODO: move this to the collider and only transform when required
    for (int i = 0; i < p1.Size(); ++i) {
        p1[i] = *poly1.transform * p1[i];
    }
    for (int i = 0; i < p2.Size(); ++i) {
        p2[i] = *poly1.transform * p2[i];
    }


    Vector2D smallestNormal;
    float smallestNormalMag = 10000;


    for (int i = 0; i < p1.Size(); ++i) {
        //next vertex
        Vector2D next = (i + 1) < poly1.polyverts->Size() ? p1[i + 1] : p1[0];

        //get edge normal
        Vector2D normal = next - p1[i];
        normal = Vector2D(normal.y, -normal.x).Normalized();

        //TODO: check if normal needs to be inverted

        float min = p1[0].DotProduct(normal);
        float max = p1[0].DotProduct(normal);

        //find the min and max projected verts for poly1
        for (int v = 1; v < p1.Size(); ++v) {
            //project the verts
            float vert = p1[v].DotProduct(normal);
            if (vert < min)
                min = vert;
            if (vert > max)
                max = vert;
        }

        bool intersecting = false;
        float maxMagnitude = 0;

        //project all the verts for poly2 and determine if they intersect min or max
        for (int v = 0; v < p2.Size(); ++v) {
            //project the vertex
            float vert = p2[v].DotProduct(normal);
            
            if (vert > min&& vert < max) {
                //potential intersection
                intersecting = true;

                float magnitude = std::min(std::abs(min - vert), std::abs(max - vert));
                if (magnitude > maxMagnitude) {
                    maxMagnitude = magnitude;
                }
            }
        }

        if (!intersecting) {
            return false;
        }

        if (maxMagnitude < smallestNormalMag) {
            smallestNormalMag = maxMagnitude;
            smallestNormal = normal;
        }
    }

    intersectVector = smallestNormal * smallestNormalMag;

    return true;

}

// Check whether a polygon and circle intersect.
// Params:
//  polygon = The polygon.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool PolygonCircleIntersection(PolygonColliderInfo polygon, const Beta::Circle& circle, Beta::Vector2D& intersectVector) {

    //Data::Vector<Vector2D>& p1 = *poly1.polyverts;
    //Data::Vector<Vector2D>& p2 = *poly2.polyverts;

    Data::Vector<Vector2D> p = *polygon.polyverts;

    //TODO: move this to the collider and only transform when required
    for (int i = 0; i < p.Size(); ++i) {
        p[i] = *polygon.transform * p[i];
    }


    Vector2D smallestNormal;
    float smallestNormalMag = 10000;


    for (int i = 0; i < p.Size(); ++i) {
        //next vertex
        Vector2D next = (i + 1) < polygon.polyverts->Size() ? p[i + 1] : p[0];

        //get edge normal
        Vector2D normal = next - p[i];
        normal = Vector2D(normal.y, -normal.x).Normalized();

        //TODO: check if normal needs to be inverted

        float min = p[0].DotProduct(normal);
        float max = p[0].DotProduct(normal);

        //find the min and max projected verts for poly1
        for (int v = 1; v < p.Size(); ++v) {
            //project the verts
            float vert = p[v].DotProduct(normal);
            if (vert < min)
                min = vert;
            if (vert > max)
                max = vert;
        }

        bool intersecting = false;
        float maxMagnitude = 0;

        //project points on either side of the circle onto the normal vector
        
        //project the vertex
        float vert = (circle.center + normal * circle.radius).DotProduct(normal);
        if (vert > min&& vert < max) {
            //potential intersection
            intersecting = true;

            float magnitude = std::min(std::abs(min - vert), std::abs(max - vert));
            if (magnitude > maxMagnitude) {
                maxMagnitude = magnitude;
            }
        }

        //project the vertex
        vert = (circle.center - normal * circle.radius).DotProduct(normal);
        if (vert > min&& vert < max) {
            //potential intersection
            intersecting = true;

            float magnitude = std::min(std::abs(min - vert), std::abs(max - vert));
            if (magnitude > maxMagnitude) {
                maxMagnitude = magnitude;
            }
        }

        if (!intersecting) {
            return false;
        }

        if (maxMagnitude < smallestNormalMag) {
            smallestNormalMag = maxMagnitude;
            smallestNormal = normal;
        }
    }

    //now check from the circle normal
    //the circle normal is the normal to the line from the circle center to the nearest vertex on the polygon

    //find the closest vertex to the circle center
    float minDist = p[0].DistanceSquared(circle.center);
    int closestIndex = 0;
    for (int i = 1; i < p.Size(); ++i) {
        float dist = p[0].DistanceSquared(circle.center);
        if (dist < minDist) {
            minDist = dist;
            closestIndex = i;
        }
    }

    //find the circle normal
    Vector2D circleNormal = circle.center - p[closestIndex];
    circleNormal = Vector2D(circleNormal.y, -circleNormal.x).Normalized();

    //get the minmax values for the polygons projected verts
    float min = p[0].DotProduct(circleNormal);
    float max = p[0].DotProduct(circleNormal);

    //find the min and max projected verts for poly1
    for (int v = 1; v < p.Size(); ++v) {
        //project the verts
        float vert = p[v].DotProduct(circleNormal);
        if (vert < min)
            min = vert;
        if (vert > max)
            max = vert;
    }

    
    bool intersect = false;
    float maxMagnitude = 0;

    //project the vertex
    float vert = (circle.center + circleNormal * circle.radius).DotProduct(circleNormal);
    if (vert > min&& vert < max) {
        //sucsessful intersection
        intersect = true;

        float magnitude = std::min(std::abs(min - vert), std::abs(max - vert));
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
        }
    }

    //project the vertex
    float vert = (circle.center + circleNormal * circle.radius).DotProduct(circleNormal);
    if (vert > min&& vert < max) {
        //sucsessful intersection
        intersect = true;

        float magnitude = std::min(std::abs(min - vert), std::abs(max - vert));
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
        }
    }

    if (!intersect) {
        return false;
    }

    if (maxMagnitude < smallestNormalMag) {
        smallestNormalMag = maxMagnitude;
        smallestNormal = circleNormal;
    }


    intersectVector = smallestNormal * smallestNormalMag;

    return true;

}

//------------------------------------------------------------------------------