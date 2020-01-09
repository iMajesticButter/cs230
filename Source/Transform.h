//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Matrix2DStudent.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Transform.h.
// You are free to change the contents of this structure as long as you do not
//   change the public method declarations declared in the header.
class Transform {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Transform constructor.
    // Params:
    //	 x = Initial world position on the x-axis.
    //	 y = Initial world position on the y-axis.
    Transform(float x, float y);

    // Transform constructor.
    // Params:
    //	 translation = World position of the object.
    //   scale		 = Width and height of the object.
    //   rotation	 = Rotation of the object about the z-axis.
    Transform(Beta::Vector2D translation = Beta::Vector2D(), Beta::Vector2D scale = Beta::Vector2D(1, 1), float rotation = 0);

    // Get the transform matrix, based upon translation, rotation and scale settings.
    // Returns:
    //	 A reference to the component's matrix structure
    const CS230::Matrix2D& GetMatrix() const;

    // Set the translation of a transform component.
    // Params:
    //	 translation = Reference to a translation vector.
    void SetTranslation(const Beta::Vector2D& translation);

    // Get the translation of a transform component.
    // Returns:
    //	 A reference to the component's translation structure.
    const Beta::Vector2D& GetTranslation() const;

    // Set the rotation of a transform component.
    // Params:
    //	 rotation = The rotation value (in radians).
    void SetRotation(float rotation);

    // Get the rotation value of a transform component.
    // Returns:
    //	 The component's rotation value (in radians).
    float GetRotation() const;

    // Set the scale of a transform component.
    // Params:
    //	 translation = Reference to a scale vector.
    void SetScale(const Beta::Vector2D& scale);

    // Get the scale of a transform component.
    // Returns:
    //	 A reference to the component's scale structure.
    const Beta::Vector2D& GetScale() const;

    // Get the forward vector of the transformed object
    // Returns:
    //    A forward vector
    const Beta::Vector2D& Forward() const;

    // Get the left vector of the transformed object
    // Returns:
    //    A left vector
    const Beta::Vector2D& Left() const;

private:

    //------------------------------------------------------------------------------
    // Private Funcs:
    //------------------------------------------------------------------------------

    // Calculate the forward and left vectors
    void CalculateDirectionVectors();

    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // The translation (or world position) of a game object.
    Beta::Vector2D m_translation;

    // The rotation (or orientation) of a game object.
    float m_rotation;

    // The scale (or size) of a game object.
    Beta::Vector2D m_scale;

    // The transformation matrix resulting from multiplying the 
    // translation, rotation, and scale matrices.
    mutable CS230::Matrix2D	m_matrix;

    // True if the transformation matrix needs to be recalculated.
    mutable bool isDirty;

    // the forward vector of the transform
    Beta::Vector2D m_forward;

    // the left vector of the transform
    Beta::Vector2D m_left;
};
//------------------------------------------------------------------------------
