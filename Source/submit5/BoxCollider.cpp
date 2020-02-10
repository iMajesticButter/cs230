//------------------------------------------------------------------------------
//
// File Name:	BoxCollider.cpp
// Author(s):	Brandon Wolenetz
// Project:		lab 6 collision detection
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "BoxCollider.h"
#include "Matrix2DStudent.h"

// default constructor
BoxCollider::BoxCollider(float width, float height, float rotation) {
    CS230::Matrix2D rotMat = CS230::Matrix2D::RotationMatrixDegrees(rotation);

    m_verts.push_back(rotMat * Beta::Vector2D(-width / 2, -height / 2));
    m_verts.push_back(rotMat * Beta::Vector2D(+width / 2, -height / 2));
    m_verts.push_back(rotMat * Beta::Vector2D(+width / 2, +height / 2));
    m_verts.push_back(rotMat * Beta::Vector2D(-width / 2, +height / 2));
}

COMPONENT_SUBCLASS_DEFINITIONS(PolygonCollider, BoxCollider)