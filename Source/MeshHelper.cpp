//------------------------------------------------------------------------------
//
// File Name:	MeshHelper.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "MeshHelper.h"

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
        Beta::Mesh* CreateTriangleMesh(const Beta::Color& color0, const Beta::Color& color1, const Beta::Color& color2) {

            auto meshFactory = EngineGetModule(Beta::MeshFactory);

            Vertex v0 = Vertex(Vector2D(-0.5f, +0.5f), color0);
            Vertex v1 = Vertex(Vector2D(-0.5f, -0.5f), color1);
            Vertex v2 = Vertex(Vector2D(+0.5f, +0.0f), color2);

            meshFactory->AddTriangle(v0, v1, v2);

            return meshFactory->EndCreate();

        }

        // Create a textured quad mesh using the Beta Framework.
        // Params:
        //   textureSize = The UV size of the mesh, in texture coordinates.
        //	 extents	 = The XY distance of the vertices from the origin.
        // Returns:
        //	 A pointer to the newly created mesh.
        Beta::Mesh* CreateQuadMesh(const Beta::Vector2D& textureSize, const Beta::Vector2D& extents) {

            auto meshFactory = EngineGetModule(Beta::MeshFactory);

            Vertex v0 = Vertex(Vector2D(-extents.x, +extents.y), Vector2D(0, 0));
            Vertex v1 = Vertex(Vector2D(+extents.x, +extents.y), Vector2D(textureSize.x, 0));
            Vertex v2 = Vertex(Vector2D(+extents.x, -extents.y), Vector2D(textureSize.x, textureSize.y));
            Vertex v3 = Vertex(Vector2D(-extents.x, -extents.y), Vector2D(0, textureSize.y));

            meshFactory->AddTriangle(v0, v1, v2);
            meshFactory->AddTriangle(v0, v3, v2);

            return meshFactory->EndCreate();

        }

        //------------------------------------------------------------------------------
    }
}