//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.cpp
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
#include "Matrix2DStudent.h"

//------------------------------------------------------------------------------

namespace CS230 {

    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Constructor for matrix. Sets all data in matrix to 0.
    Matrix2D::Matrix2D() : m{{0,0,0},{0,0,0},{0,0,0}} {

    }

    // This function creates an identity matrix and returns it.
    Matrix2D Matrix2D::IdentityMatrix() {
        Matrix2D mat;
        mat[0][0] = 1;
        mat[1][1] = 1;
        mat[2][2] = 1;
        return mat;
    }

    // This function calculates the transpose matrix of Mtx and saves it in the result matrix.
    // (NOTE: Care must be taken when pResult = pMtx.)
    Matrix2D Matrix2D::Transposed() const {
        Matrix2D mat;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                mat[r][c] = m[c][r];
            }
        }
        return mat;
    }

    // This function creates a translation matrix from x & y and returns it.
    Matrix2D Matrix2D::TranslationMatrix(float x, float y) {
        Matrix2D mat = IdentityMatrix();
        mat[0][2] = x;
        mat[1][2] = y;
        return mat;
    }

    // This function creates a scaling matrix from x & y and returns it.
    Matrix2D Matrix2D::ScalingMatrix(float x, float y) {
        Matrix2D mat = IdentityMatrix();
        mat[0][0] = x;
        mat[1][1] = y;
        return mat;
    }

    // This matrix creates a rotation matrix from "Angle" whose value is in degrees.
    // Return the resulting matrix.
    // Converting from degrees to radians can be performed as follows:
    //	 radians = (angle * M_PI) / 180.0f
    Matrix2D Matrix2D::RotationMatrixDegrees(float angle) {
        return RotationMatrixRadians((angle * (float)M_PI) / 180.0f);
    }

    // This matrix creates a rotation matrix from "Angle" whose value is in radians.
    // Return the resulting matrix.
    Matrix2D Matrix2D::RotationMatrixRadians(float angle) {
        float csa = cos(angle);
        float sa = sin(angle);

        Matrix2D mat = IdentityMatrix();
        mat[0][0] = csa;
        mat[0][1] = -sa;
        mat[1][0] = sa;
        mat[1][1] = csa;
        return mat;
    }

    // This function multiplies the current matrix with another and returns the result as a new matrix.
    // HINT: Use the RowColumnMultiply function to help write this function.
    Matrix2D Matrix2D::operator*(const Matrix2D& other) const {
        Matrix2D mat;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                mat[r][c] = RowColumnMultiply(other, r, c);
            }
        }
        return mat;
    }

    // This function multiplies the current matrix with another, storing the result in the current matrix.
    // HINT: Use the RowColumnMultiply function to help write this function.
    Matrix2D& Matrix2D::operator*=(const Matrix2D& other) {
        *this = *this * other;
        return *this;
    }

    // This function multiplies a matrix with a vector and returns the result as a new vector.
    // Result = Mtx * Vec.
    Beta::Vector2D Matrix2D::operator*(const Beta::Vector2D& vec) const {
        float x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2];
        float y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2];
        
        return Beta::Vector2D(x, y);
    }

    // return weather the matrix is the same as another matrix
    bool Matrix2D::operator==(const Matrix2D& other) const {
        return m[0][0] == other.m[0][0] && m[1][0] == other.m[1][0] && m[2][0] == other.m[2][0] &&
               m[0][1] == other.m[0][1] && m[1][1] == other.m[1][1] && m[2][1] == other.m[2][1] &&
               m[0][2] == other.m[0][2] && m[1][2] == other.m[1][2] && m[2][2] == other.m[2][2];
    }

    // return weather the matrix is different from another matrix
    bool Matrix2D::operator!=(const Matrix2D& other) const {
        return m[0][0] != other.m[0][0] || m[1][0] != other.m[1][0] || m[2][0] != other.m[2][0] ||
               m[0][1] != other.m[0][1] || m[1][1] != other.m[1][1] || m[2][1] != other.m[2][1] ||
               m[0][2] != other.m[0][2] || m[1][2] != other.m[1][2] || m[2][2] != other.m[2][2];
    }

    // access operator for the matrix
    float* Matrix2D::operator[](int index) {
        return m[index];
    }

    //------------------------------------------------------------------------------
    // Private Functions:
    //------------------------------------------------------------------------------

    // Multiplies a row of the current matrix by a column in another and returns the result.
    float Matrix2D::RowColumnMultiply(const Matrix2D& other, unsigned r, unsigned c) const {
        return m[r][0] * other.m[0][c] + m[r][1] * other.m[1][c] + m[r][2] * other.m[2][c];
    }
}

//------------------------------------------------------------------------------
