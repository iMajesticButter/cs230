//------------------------------------------------------------------------------
//
// File Name:	BoxCollider.h
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once


#include "PolygonCollider.h"

class BoxCollider : public PolygonCollider {
public:

    // default constructor
    // params:
    //  width is the width of the box collider relative to the object
    //  height is the height of the box collider relative to the object
    //  rotation is the rotation angle in degrees of the box collider relative to the object
    BoxCollider(float width = 1, float height = 1, float rotation = 0);

private:

    COMPONENT_SUBCLASS_DECLARATIONS(BoxCollider)

};