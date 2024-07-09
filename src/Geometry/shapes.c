#include "Geometry/shapes.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int maxDim = 3;

float _degsToRads(float angleDegs) { return (angleDegs * PI) / 180.0f; }

void mapShapeToGLVertices(Point* shape, GLfloat* vertices, int verticesCount, int dim) {
    assert(dim > 0 && dim <= maxDim);
    for (int i = 0; i < verticesCount; i++) {
        memcpy(&(vertices[i * maxDim]), &(shape[i]), dim * sizeof(GLfloat));
        memset(&(vertices[i * maxDim + dim]), 0.0f, (maxDim - dim) * sizeof(GLfloat));
    }
}

void rotateShape(Point* shape, int verticesCount, float angleDegs, Point pointOfRotation) {
    float angleRads = _degsToRads(angleDegs);
    float cosA = cos(angleRads);
    float sinA = sin(angleRads);
    for (int i = 0; i < verticesCount; i++) {
        Point* point = &(shape[i]);
        float xDiff = point->x - pointOfRotation.x;
        float yDiff = point->y - pointOfRotation.y;
        point->x = pointOfRotation.x + (xDiff)*cosA - (yDiff)*sinA;
        point->y = pointOfRotation.y + (xDiff)*sinA + (yDiff)*cosA;
    }
}