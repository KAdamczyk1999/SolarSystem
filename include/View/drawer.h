#pragma once

#include "Geometry/shapes.h"

#ifdef __cplusplus
extern "C" {
#endif

void drawShapeArray(Shape* shapes, int shapeCount, GLuint shaderProgram);

void drawCircle(Point point, float radius, GLuint shaderProgram);

#ifdef __cplusplus
}
#endif