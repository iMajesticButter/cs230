//------------------------------------------------------------------------------
//
// File Name:	MeshHelper.h
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

#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

namespace Beta {
    class Mesh;
    struct Color;
}

namespace Beta {
    namespace MeshHelper {

        //------------------------------------------------------------------------------
        // Public Functions:
        //------------------------------------------------------------------------------

        // Create a colored mesh consisting of a single triangle using the Beta Framework.
        // Params:
        //   color0 = The color of vertex 0.
        //   color1 = The color of vertex 1.
        //   color2 = The color of vertex 2.
        // Returns:
        //	 A pointer to the newly created mesh.
        Beta::Mesh* CreateTriangleMesh(const Beta::Color& color0, const Beta::Color& color1, const Beta::Color& color2);

        // Create a textured quad mesh using the Beta Framework.
        // Params:
        //   textureSize = The UV size of the mesh, in texture coordinates.
        //	 extents	 = The XY distance of the vertices from the origin.
        // Returns:
        //	 A pointer to the newly created mesh.
        Beta::Mesh* CreateQuadMesh(const Beta::Vector2D& textureSize = Beta::Vector2D(1.0f, 1.0f), const Beta::Vector2D& extents = Beta::Vector2D(0.5f, 0.5f));

        //------------------------------------------------------------------------------
    }
}
