//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include <string.h>

namespace Beta {
    class Vector2D;
    class Texture;
}


class SpriteSource {
public:

    //public funcs

    //! constructor
    /*!
      /param texture the texture that contains the frames that this sprite will use
      /param name the name to use for this sprite source
      /param numCols the number of total columns in the sprite sheet texture
      /param numRows the number of total rows in the sprite sheet texture
    */
    SpriteSource(const Beta::Texture* texture = nullptr, std::string name = "", unsigned numCols = 1, unsigned numRows = 1);

    //! activates the sprite source texture and sets its UV offset based on the given frame index
    /*!
      /param frameIndex the index of the frame of the texture that we want to use
      /param flipX whether to flip the sprite horizontally when rendering
      /param flipY whether to flip the sprite vertically when rendering
      /param shader the shader to use the spriteSource with, defaults to sprite shader
    */
    void UseTexture(unsigned frameIndex = 0, bool flipX = false, bool flipY = false, const Beta::ShaderProgram* shader = nullptr) const;

    //! returns the maximum number of possible frames in the sprite source's texture (rows * cols).
    unsigned GetFrameCount() const;

    //! gets the name of the sprite source
    const std::string& GetName() const;

    //! gets the dimentions of the texture (number of columns, rows)
    const Beta::Vector2D GetTextureDimentions() const;

private:

    //private funcs

    //! returns the UV coordinates of the specified frame in a sprite sheet
    /*!
      /param frameIndex a frame index within a sprite sheet
      /returns a vector containing the UV/texture coordinates
    */
    const Beta::Vector2D GetUV(unsigned frameIndex) const;

    // private variables

    // sprite sheet dimentions
    unsigned m_numRows;
    unsigned m_numCols;

    // pointer to a texture created using the low level API
    const Beta::Texture* m_texture;

    // the name of the sprite source
    std::string m_name;

};