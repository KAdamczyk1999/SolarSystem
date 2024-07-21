#pragma once
#include <stdlib.h>

#include "Geometry/shapes.h"

#define SHAPE_COUNT 8
Point* triangleVerticesTab[SHAPE_COUNT];
Shape myShapes[SHAPE_COUNT];

void createShapes() {
    for (int i = 0; i < SHAPE_COUNT; i++) {
        triangleVerticesTab[i] = (Point*)malloc(3 * sizeof(Point));
        for (int j = 0; j < 3; j++) {
            triangleVerticesTab[i][j].x = .01 * j - .01;
            triangleVerticesTab[i][j].y = (i + 1) * 0.05 - 0.01 + 0.02 * (j % 2);
        }
        myShapes[i].vertices = triangleVerticesTab[i];
        myShapes[i].verticesCount = 3;
        myShapes[i].drawingMethod = GL_TRIANGLES;
    }
}
