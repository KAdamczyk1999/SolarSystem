#pragma once
#include "Geometry/shapes.h"

#define SHAPE_COUNT 3
Point triangle1Vertices[] = {{0.0f, -0.125f}, {0.1f, 0.0f}, {0.0f, 0.125f}};
Point triangle2Vertices[] = {{-.125f, 0.25f}, {0.0f, .375f}, {.125f, 0.25f}};
Point triangle3Vertices[] = {{-.25f, 0.5f}, {0.0f, .75f}, {.25f, 0.5f}};
Shape myShapes[] = {
    {triangle1Vertices, 3, GL_TRIANGLES},
    {triangle2Vertices, 3, GL_TRIANGLES},
    {triangle3Vertices, 3, GL_TRIANGLES},
};
