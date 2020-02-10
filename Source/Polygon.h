//------------------------------------------------------------------------------
//
// File Name:	Polygon.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Matrix2DStudent.h"
#include "betaVector.h"


//a simple storage class that contains pointers to a polygon colliders vertecies and transform matrix
struct PolygonColliderInfo {
public:
    Beta::Data::Vector<Beta::Vector2D>* polyverts;
    //CS230::Matrix2D* transform;
    //TODO: add a bounding box to the info
};