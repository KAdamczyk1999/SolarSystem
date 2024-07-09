#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <glad/glad.h>
#include <glfw/glfw3.h>

#define PI 3.141592654

typedef struct {
    float x;
    float y;
} Point;

typedef Point Triangle[3];

void mapShapeToGLVertices(Point* shape, GLfloat* vertices, int verticesCount);

void rotateShape(Point* shape, int verticesCount, float angleDegs, Point pointOfRotation);

#ifdef __cplusplus
}
#endif