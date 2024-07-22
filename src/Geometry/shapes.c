#include "Geometry/shapes.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int maxDim = 3;

float _degsToRads(float angleDegs) { return (angleDegs * PI) / 180.0f; }

void mapShapeToGLVertices(Shape shape, GLfloat* vertices, int dim) {
    assert(dim > 0 && dim <= maxDim);
    for (int i = 0; i < shape.verticesCount; i++) {
        memcpy(&(vertices[i * maxDim]), &(shape.vertices[i]), dim * sizeof(GLfloat));
        memset(&(vertices[i * maxDim + dim]), 0.0f, (maxDim - dim) * sizeof(GLfloat));
    }
}

void rotatePoint(Point* point, float angleDegs, Point pointOfRotation) {
    float angleRads = _degsToRads(angleDegs);
    float cosA = cos(angleRads);
    float sinA = sin(angleRads);
    float xDiff = point->x - pointOfRotation.x;
    float yDiff = point->y - pointOfRotation.y;
    point->x = pointOfRotation.x + (xDiff)*cosA - (yDiff)*sinA;
    point->y = pointOfRotation.y + (xDiff)*sinA + (yDiff)*cosA;
}

void rotateShape(Shape* shape, float angleDegs, Point pointOfRotation) {
    for (int i = 0; i < shape->verticesCount; i++) {
        rotatePoint(&(shape->vertices[i]), angleDegs, pointOfRotation);
    }
}

Point getShapeCenter(Shape shape) {
    Point point = {0.0f, 0.0f, 0.0f};
    for (int i = 0; i < shape.verticesCount; i++) {
        point.x += shape.vertices[i].x;
        point.y += shape.vertices[i].y;
        point.z += shape.vertices[i].z;
    }
    point.x /= shape.verticesCount;
    point.y /= shape.verticesCount;
    point.z /= shape.verticesCount;
    return point;
}