//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Sprite.h"
#include "MeshHelper.h"

//Sprite

//! Constructor
Sprite::Sprite(SpriteSource* spriteSource, Beta::Mesh* mesh) : m_spriteSource(spriteSource), m_mesh(mesh),
              m_color(Beta::Colors::White), m_shader(nullptr), m_flipX(false), m_flipY(false), m_frame(0) {
}

//! draw the sprite to the screen
void Sprite::Draw() {

    if (m_mesh == nullptr)
        return;

    auto graphics = EngineGetModule(Beta::GraphicsEngine);

    const Beta::ShaderProgram* shader;

    if (m_shader == nullptr)
        shader = &graphics->GetSpriteShader();
    else
        shader = m_shader;

    shader->Use();

    if (m_spriteSource != nullptr) {

    } else {
        graphics->GetDefaultTexture().Use(Beta::Vector2D(), shader);
    }

    graphics->SetSpriteBlendColor(m_color);

    //transformation matrix
    Beta::Matrix2D translationMat = Beta::Matrix2D::TranslationMatrix(0, 0);
    Beta::Matrix2D rotationMat = Beta::Matrix2D::RotationMatrixRadians(0);
    Beta::Matrix2D scaleMat = Beta::Matrix2D::ScalingMatrix(1, 1);

    graphics->SetTransform(translationMat * rotationMat * scaleMat);

    //draw
    m_mesh->Draw();

}

//! set the sprite's alpha
/*!
  /param alpha the new alpha for the sprite
*/
void Sprite::SetAlpha(float alpha) {
    m_color.a = alpha;
}

//! get the sprite's alpha
/*!
  /returns the sprite's current alpha
*/
float Sprite::GetAlpha() {
    return m_color.a;
}

//! set the current frame of the sprite
/*!
  /param frame the frame to display
*/
void Sprite::SetFrame(unsigned frame) {
    m_frame = frame;
}

//! set the mesh
void Sprite::SetMesh(Beta::Mesh* mesh) {
    m_mesh = mesh;
}

//! get the mesh
Beta::Mesh* Sprite::GetMesh() {
    return m_mesh;
}

//! set the spriteSource
void Sprite::SetSpriteSource(SpriteSource* spriteSource) {
    m_spriteSource = spriteSource;
}

//! get the spriteSource
SpriteSource* Sprite::GetSpriteSource() {
    return m_spriteSource;
}

//! set the sprite color
void Sprite::SetColor(const Beta::Color& color) {
    m_color = color;
}

//! get the sprite color
Beta::Color Sprite::GetColor() {
    return m_color;
}

//! flip the sprite on the x axis
void Sprite::FlipX(bool flipX) {
    m_flipX = flipX;
}

//! flip the sprite on the y axis
void Sprite::FlipY(bool flipY) {
    m_flipY = flipY;
}

//! is the sprite flipped on the x axis
bool Sprite::IsFlippedX() {
    return m_flipX;
}

//! is the sprite flipped on the y axis
bool Sprite::IsFlippedY() {
    return m_flipY;
}

//! set the sprites shader
void Sprite::SetShader(Beta::ShaderProgram* shader) {
    m_shader = shader;
}

//! get the sprites shader
Beta::ShaderProgram* Sprite::GetShader() {
    return m_shader;
}