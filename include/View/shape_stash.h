#pragma once
#include <stdlib.h>

#include "Geometry/shapes.h"

#define SHAPE_COUNT 8
Point triangleVerticesTab[SHAPE_COUNT][3];
Shape satelites[SHAPE_COUNT];

void createSatelites() {
    for (int i = 0; i < SHAPE_COUNT; i++) {
        for (int j = 0; j < 3; j++) {
            triangleVerticesTab[i][j].x = .01 * j - .01;
            triangleVerticesTab[i][j].y = (i + 1) * 0.09 - 0.01 + 0.02 * (j % 2);
        }
        satelites[i].vertices = triangleVerticesTab[i];
        satelites[i].verticesCount = 3;
        satelites[i].drawingMethod = GL_TRIANGLES;
    }
}
