#include "View/drawer.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

const int dimentions = 3;

void _setUpShape(Shape shape, int shapeIndex, GLuint* VAO, GLuint* VBO) {
    glBindVertexArray(VAO[shapeIndex]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[shapeIndex]);

    float verticesCount = shape.verticesCount;

    GLfloat* shapeVertices = malloc(verticesCount * dimentions * sizeof(GLfloat));
    mapShapeToGLVertices(shape, shapeVertices, 2);

    glBufferData(GL_ARRAY_BUFFER, verticesCount * dimentions * sizeof(GLfloat), shapeVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, verticesCount, GL_FLOAT, GL_FALSE, verticesCount * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    free(shapeVertices);
}

void _drawShape(Shape shape, int shapeIndex, GLuint* VAO) {
    glBindVertexArray(VAO[shapeIndex]);
    glDrawArrays(shape.drawingMethod, 0, shape.verticesCount);
}

void drawShapeArray(Shape* shapes, int shapeCount, GLuint shaderProgram) {
    GLuint* VAO = (GLuint*)malloc(shapeCount * sizeof(Shape));
    GLuint* VBO = (GLuint*)malloc(shapeCount * sizeof(Shape));
    glGenVertexArrays(shapeCount, VAO);
    glGenBuffers(shapeCount, VBO);

    for (int i = 0; i < shapeCount; i++) {
        _setUpShape(shapes[i], i, VAO, VBO);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    for (int i = 0; i <= shapeCount; i++) {
        _drawShape(shapes[i], i, VAO);
    }
    glUseProgram(0);

    glDeleteVertexArrays(shapeCount, VAO);
    glDeleteBuffers(shapeCount, VBO);

    free(VAO);
    free(VBO);
}

void drawCircle(Circle circle, GLuint shaderProgram) {
#define STEPS 50
    Shape shapes[STEPS + 1];
    const float angle = 360.0f / STEPS;
    Point prevPoint = {circle.centerPoint.x, circle.centerPoint.y - circle.radius};

    for (int i = 0; i <= STEPS; i++) {
        Point newPoint = prevPoint;
        rotatePoint(&newPoint, angle, circle.centerPoint);
        Point shapeVertices[3] = {circle.centerPoint, {prevPoint.x, prevPoint.y, 0.0f}, {newPoint.x, newPoint.y, 0.0f}};
        shapes[i].vertices = (Point*)malloc(sizeof(shapeVertices));
        memcpy(shapes[i].vertices, shapeVertices, sizeof(shapeVertices));
        shapes[i].verticesCount = 3;
        shapes[i].drawingMethod = GL_TRIANGLES;

        prevPoint = newPoint;
    }

    drawShapeArray(shapes, STEPS + 1, shaderProgram);

    for (int i = 0; i <= STEPS; i++) {
        free(shapes[i].vertices);
    }
}