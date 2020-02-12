//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SpriteTilemap.h"
#include "SpriteSource.h"
#include "Tilemap.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new sprite for use with a tilemap.
SpriteTilemap::SpriteTilemap(Beta::Mesh* mesh, SpriteSource* spriteSource, const Tilemap* map) : 
        Sprite(spriteSource, mesh), m_map(map) {

}

// Draw a sprite (Sprite can be textured or untextured).
void SpriteTilemap::Draw() {

    unsigned columns = m_map->GetWidth();
    unsigned rows = m_map->GetHeight();

    Beta::Vector2D tileSize = transform()->GetScale();

    for (unsigned r = 0; r < rows; ++r) {
        for (unsigned c = 0; c < columns; ++c) {
            int cellValue = m_map->GetCellValue(c, r);

            if (cellValue != 0) {
                m_frame = cellValue-1;
                if (cellValue < 0)
                    m_frame = 10;

                Beta::Vector2D offset = Beta::Vector2D((c * tileSize.x), ((-(int)r) * tileSize.y));

                Sprite::Draw(offset);
            }

        }
    }

}

// Sets the tilemap data that will be used by the sprite.
// Params:
//   map = A pointer to the tilemap resource.
void SpriteTilemap::SetTilemap(const Tilemap* map) {
    m_map = map;
}

COMPONENT_SUBCLASS_DEFINITIONS(Sprite, SpriteTilemap)