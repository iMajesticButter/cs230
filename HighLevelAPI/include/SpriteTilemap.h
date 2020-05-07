//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.h
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

#include "Sprite.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Tilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class SpriteTilemap : public Sprite {
public:
    //------------------------------------------------------------------------------
    // Public Functions:
    //------------------------------------------------------------------------------

    // Create a new sprite for use with a tilemap.
    SpriteTilemap(Beta::Mesh* mesh, SpriteSource* spriteSource = nullptr, const Tilemap* map = nullptr);

    // Draw a sprite (Sprite can be textured or untextured).
    void Draw() override;

    // Sets the tilemap data that will be used by the sprite.
    // Params:
    //   map = A pointer to the tilemap resource.
    void SetTilemap(const Tilemap* map);

private:
    //------------------------------------------------------------------------------
    // Private Variables:
    //------------------------------------------------------------------------------

    // The tilemap
    const Tilemap* m_map;

    COMPONENT_SUBCLASS_DECLARATIONS(SpriteTilemap)
};

//------------------------------------------------------------------------------
