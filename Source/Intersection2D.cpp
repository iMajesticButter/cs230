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
        intersectVector = (circle.center - point).Normalized() * (circle.radius - dist);

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
    //bool intersect = PolygonCircleIntersection(polygon, Circle(point, 0), intersectVector);
    //intersectVector = -intersectVector;
    //return intersect;
    return PolygonCircleIntersection(polygon, Circle(point, 0), intersectVector);
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
        intersectVector = (circle2.center - circle1.center).Normalized() * (combinedRadius - dist);

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

    Data::Vector<Vector2D>& p1 = *poly1.polyverts;
    Data::Vector<Vector2D>& p2 = *poly2.polyverts;

    //Data::Vector<Vector2D> p1 = *poly1.polyverts;
    //Data::Vector<Vector2D> p2 = *poly2.polyverts;

    /*for (int i = 0; i < p1.Size(); ++i) {
        p1[i] = *poly1.transform * p1[i];
    }
    for (int i = 0; i < p2.Size(); ++i) {
        p2[i] = *poly1.transform * p2[i];
    }*/


    Vector2D smallestNormal;
    float smallestNormalMag = 10000;


    for (int i = 0; i < p1.Size(); ++i) {

        //next vertex
        Vector2D next = ((int)i + 1) < p1.Size() ? p1[(int)i + 1] : p1[0];
        
        //get edge normal
        Vector2D normal = next - p1[i];
        normal = Vector2D(normal.y, -normal.x).Normalized();

        //TODO: check if normal needs to be inverted

        float min = p1[0].DotProduct(normal);
        float max = min;

        //find the min and max projected verts for poly1
        for (int v = 1; v < p1.Size(); ++v) {
            //project the verts
            float vert = p1[v].DotProduct(normal);
            if (vert < min)
                min = vert;
            if (vert > max)
                max = vert;
        }

        float poly2min = p2[0].DotProduct(normal);
        float poly2max = poly2min;

        //find the minimum and maximum values for poly2
        for (int v = 1; v < p2.Size(); ++v) {
            //project the verts
            float vert = p2[v].DotProduct(normal);
            if (vert < poly2min)
                poly2min = vert;
            if (vert > poly2max)
                poly2max = vert;
        }

        if (max > poly2min && min < poly2max) {

            float normalLength;

            if (max - poly2min < poly2max - min) {
                normalLength = max - poly2min;
            } else {
                normalLength = poly2max - min;
                normal = -normal;
            }

            if (normalLength < smallestNormalMag) {
                smallestNormalMag = normalLength;
                smallestNormal = normal;
            }

        } else {
            return false;
        }


        //if (!intersecting) {
        //    return false;
        //}

        /*if (maxMagnitude < smallestNormalMag) {
            smallestNormalMag = maxMagnitude;
            smallestNormal = normal;
        }*/
    }

    intersectVector = smallestNormal.Normalized() * smallestNormalMag;

    return true;

}

// Check whether a polygon and circle intersect.
// Params:
//  polygon = The polygon.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool PolygonCircleIntersection(PolygonColliderInfo polygon, const Beta::Circle& circle, Beta::Vector2D& intersectVector) {
    Data::Vector<Vector2D>& p = *polygon.polyverts;

    //Data::Vector<Vector2D> p1 = *poly1.polyverts;
    //Data::Vector<Vector2D> p2 = *poly2.polyverts;

    /*for (int i = 0; i < p1.Size(); ++i) {
        p1[i] = *poly1.transform * p1[i];
    }
    for (int i = 0; i < p2.Size(); ++i) {
        p2[i] = *poly1.transform * p2[i];
    }*/


    Vector2D smallestNormal;
    float smallestNormalMag = 10000;


    for (int i = 0; i < p.Size(); ++i) {

        //next vertex
        Vector2D next = ((int)i + 1) < p.Size() ? p[(int)i + 1] : p[0];

        //get edge normal
        Vector2D normal = next - p[i];
        normal = Vector2D(normal.y, -normal.x).Normalized();

        //TODO: check if normal needs to be inverted

        float min = p[0].DotProduct(normal);
        float max = min;

        //find the min and max projected verts for poly1
        for (int v = 1; v < p.Size(); ++v) {
            //project the verts
            float vert = p[v].DotProduct(normal);
            if (vert < min)
                min = vert;
            if (vert > max)
                max = vert;
        }

        float projectedCenter = circle.center.DotProduct(normal);

        float poly2min = projectedCenter - circle.radius;
        float poly2max = projectedCenter + circle.radius;

        if (max > poly2min && min < poly2max) {

            float normalLength;

            if (max - poly2min < poly2max - min) {
                normalLength = max - poly2min;
            } else {
                normalLength = poly2max - min;
                normal = -normal;
            }

            if (normalLength < smallestNormalMag) {
                smallestNormalMag = normalLength;
                smallestNormal = normal;
            }

        } else {
            return false;
        }
    }

    //now check the circle-center-to-nearest-vertex normal

    //find nearest vertex to circle center

    float nearest = circle.center.DistanceSquared(p[0]);
    int nearestIndex = 0;

    for (int i = 1; i < p.Size(); ++i) {
        float dist = circle.center.DistanceSquared(p[i]);
        if (dist < nearest) {
            nearest = dist;
            nearestIndex = i;
        }
    }

    //get circle normal
    Vector2D normal = (circle.center - p[nearestIndex]).Normalized();

    float min = p[0].DotProduct(normal);
    float max = min;

    //find the min and max projected verts for poly1
    for (int v = 1; v < p.Size(); ++v) {
        //project the verts
        float vert = p[v].DotProduct(normal);
        if (vert < min)
            min = vert;
        if (vert > max)
            max = vert;
    }

    float projectedCenter = circle.center.DotProduct(normal);

    float poly2min = projectedCenter - circle.radius;
    float poly2max = projectedCenter + circle.radius;

    if (max > poly2min && min < poly2max) {

        float normalLength;

        if (max - poly2min < poly2max - min) {
            normalLength = max - poly2min;
        } else {
            normalLength = poly2max - min;
            normal = -normal;
        }

        if (normalLength < smallestNormalMag) {
            smallestNormalMag = normalLength;
            smallestNormal = normal;
        }

    } else {
        return false;
    }

    intersectVector = smallestNormal.Normalized() * smallestNormalMag;

    return true;

}

//------------------------------------------------------------------------------