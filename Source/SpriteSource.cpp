//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "SpriteSource.h"


//public funcs

//! constructor
/*!
  /param texture the texture that contains the frames that this sprite will use
  /param name the name to use for this sprite source
  /param numCols the number of total columns in the sprite sheet texture
  /param numRows the number of total rows in the sprite sheet texture
*/
SpriteSource::SpriteSource(const Beta::Texture* texture, std::string name, unsigned numCols, unsigned numRows) :
    m_texture(texture), m_numCols(numCols), m_numRows(numRows), m_name(name){
    
}

//! activates the sprite source texture and sets its UV offset based on the given frame index
/*!
  /param frameIndex the index of the frame of the texture that we want to use
  /param flipX whether to flip the sprite horizontally when rendering
  /param flipY whether to flip the sprite vertically when rendering
  /param shader the shader to use the spriteSource with, defaults to sprite shader
*/
void SpriteSource::UseTexture(unsigned frameIndex, bool flipX, bool flipY, const Beta::ShaderProgram* shader) const {
    if (shader == nullptr) {
        //use sprite shader
        shader = &EngineGetModule(Beta::GraphicsEngine)->GetSpriteShader();
    }
    
    //calculate uv offset
    Beta::Vector2D UVoffset = GetUV(frameIndex);

    //call textures use function
    m_texture->Use(1, 1, flipX, flipY, UVoffset, shader);

}

//! returns the maximum number of possible frames in the sprite source's texture (rows * cols).
unsigned SpriteSource::GetFrameCount() const {
    return m_numRows * m_numCols;
}

//! gets the name of the sprite source
const std::string& SpriteSource::GetName() const {
    return m_name;
}

//! gets the dimentions of the texture (number of columns, rows)
const Beta::Vector2D SpriteSource::GetTextureDimentions() const {
    return Beta::Vector2D((float)m_numCols, (float)m_numRows);
}

//private funcs

//! returns the UV coordinates of the specified frame in a sprite sheet
/*!
  /param frameIndex a frame index within a sprite sheet
  /returns a vector containing the UV/texture coordinates
*/
const Beta::Vector2D SpriteSource::GetUV(unsigned frameIndex) const {

    float Usize = 1.0f / (float)m_numCols;
    float Vsize = 1.0f / (float)m_numRows;

    float U = ((int)(frameIndex % m_numCols)) * Usize;
    float V = ((int)(frameIndex / m_numRows)) * Vsize;

    return Beta::Vector2D(U, V);

}