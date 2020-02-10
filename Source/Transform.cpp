//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Transform constructor.
// Params:
//	 x = Initial world position on the x-axis.
//	 y = Initial world position on the y-axis.
Transform::Transform(float x, float y) : Component("Transform"),
       m_translation(x, y), isDirty(true), m_rotation(0), m_scale(1, 1) {

    CalculateDirectionVectors();

}

// Transform constructor.
// Params:
//	 translation = World position of the object.
//   scale		 = Width and height of the object.
//   rotation	 = Rotation of the object about the z-axis.
Transform::Transform(Beta::Vector2D translation, Beta::Vector2D scale, float rotation) : Component("Transform"),
       m_translation(translation), isDirty(true), m_rotation(rotation), m_scale(scale) {

    CalculateDirectionVectors();

}

// Get the transform matrix, based upon translation, rotation and scale settings.
// Returns:
//	 A reference to the component's matrix structure
const CS230::Matrix2D& Transform::GetMatrix() const {
    using namespace CS230;
    if (isDirty) {
        m_matrix = Matrix2D::TranslationMatrix(m_translation.x, m_translation.y) * 
                   Matrix2D::RotationMatrixRadians(m_rotation) *
                   Matrix2D::ScalingMatrix(m_scale.x, m_scale.y);
        isDirty = false;
        //TODO: send some sort of event to tell all the objects components that the transform matrix has changed
    }
    return m_matrix;
}

// Set the translation of a transform component.
// Params:
//	 translation = Reference to a translation vector.
void Transform::SetTranslation(const Beta::Vector2D& translation) {
    if (m_translation.x != translation.x || m_translation.y != translation.y) {
        isDirty = true;
        m_translation = translation;
    }
}

// Get the translation of a transform component.
// Returns:
//	 A reference to the component's translation structure.
const Beta::Vector2D& Transform::GetTranslation() const {
    return m_translation;
}

// Set the rotation of a transform component.
// Params:
//	 rotation = The rotation value (in radians).
void Transform::SetRotation(float rotation) {
    if (m_rotation != rotation) {
        isDirty = true;
        m_rotation = rotation;

        //calculate forward and left vectors
        CalculateDirectionVectors();
    }
}

// Get the rotation value of a transform component.
// Returns:
//	 The component's rotation value (in radians).
float Transform::GetRotation() const {
    return m_rotation;
}

// Set the scale of a transform component.
// Params:
//	 translation = Reference to a scale vector.
void Transform::SetScale(const Beta::Vector2D& scale) {
    if (m_scale.x != scale.x || m_scale.y != scale.y) {
        isDirty = true;
        m_scale = scale;
    }
}

// Get the scale of a transform component.
// Returns:
//	 A reference to the component's scale structure.
const Beta::Vector2D& Transform::GetScale() const {
    return m_scale;
}

// Get the forward vector of the transformed object
// Returns:
//    A forward vector
const Beta::Vector2D& Transform::Forward() const {
    return m_forward;
}

// Get the left vector of the transformed object
// Returns:
//    A left vector
const Beta::Vector2D& Transform::Left() const {
    return m_left;
}

//------------------------------------------------------------------------------
// Private Funcs:
//------------------------------------------------------------------------------

// Calculate the forward and left vectors
void Transform::CalculateDirectionVectors() {
    m_forward = Beta::Vector2D(cos(m_rotation), sin(m_rotation));
    m_left = Beta::Vector2D(m_forward.y, -m_forward.x);
}

COMPONENT_CLASS_DEFINITIONS(Transform)
