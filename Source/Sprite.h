//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once


//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <Color.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

namespace Beta {
    class Mesh;
    class Vector2D;
}

class SpriteSource;
class Transform;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Sprite {
public:

    //! Constructor
    Sprite(SpriteSource* spriteSource = nullptr, Beta::Mesh* mesh = nullptr, Transform* transform = nullptr);

    //! draw the sprite to the screen
    void Draw();

    //! set the sprite's alpha
    /*!
      /param alpha the new alpha for the sprite
    */
    void SetAlpha(float alpha);

    //! get the sprite's alpha
    /*!
      /returns the sprite's current alpha
    */
    float GetAlpha();

    //! set the current frame of the sprite
    /*!
      /param frame the frame to display
    */
    void SetFrame(unsigned frame);

    //! set the mesh
    void SetMesh(Beta::Mesh* mesh);

    //! get the mesh
    Beta::Mesh* GetMesh();

    //! set the spriteSource
    void SetSpriteSource(const SpriteSource* spriteSource);

    //! get the spriteSource
    const SpriteSource* GetSpriteSource();

    //! set the sprite color
    void SetColor(const Beta::Color& color);

    //! get the sprite color
    Beta::Color GetColor();

    //! flip the sprite on the x axis
    void FlipX(bool flipX);

    //! flip the sprite on the y axis
    void FlipY(bool flipY);

    //! is the sprite flipped on the x axis
    bool IsFlippedX();

    //! is the sprite flipped on the y axis
    bool IsFlippedY();

    //! set the sprites shader
    void SetShader(Beta::ShaderProgram* shader);

    //! get the sprites shader
    Beta::ShaderProgram* GetShader();


private:

    //private variables

    const SpriteSource* m_spriteSource;
    Transform* m_transform;

    Beta::Mesh* m_mesh;
    Beta::Color m_color;

    Beta::ShaderProgram* m_shader;

    bool m_flipX;
    bool m_flipY;

    unsigned m_frame;

};