#include "View/drawer.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "Common/types.h"

#define PROPERTIES_MAX_COUNT 36000

void _setUpShape(Shape shape, int shapeIndex, GLuint* VAO, GLuint* VBO) {
    GLfloat shapeProperties[PROPERTIES_MAX_COUNT];

    glBindVertexArray(VAO[shapeIndex]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[shapeIndex]);

    int totalVals = DIMENTION_COUNT + COLOR_COUNT;

    int neededWords = shape.verticesCount * totalVals;
    assert(neededWords <= PROPERTIES_MAX_COUNT);
    int neededSpace = shape.verticesCount * sizeof(GLfloat) * totalVals;

    mapShapeToGLVertices(shape, shapeProperties, 2);

    glBufferData(GL_ARRAY_BUFFER, neededSpace, shapeProperties, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, DIMENTION_COUNT, GL_FLOAT, GL_FALSE, totalVals * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, COLOR_COUNT, GL_FLOAT, GL_FALSE, totalVals * sizeof(GLfloat),
                          (void*)(COLOR_COUNT * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void _drawShape(Shape shape, int shapeIndex, GLuint* VAO) {
    glBindVertexArray(VAO[shapeIndex]);
    glDrawArrays(shape.drawingMethod, 0, shape.verticesCount);
}

void drawShapeArray(Shape* shapes, int shapeCount, GLuint shaderProgram) {
    GLuint VAO[PROPERTIES_MAX_COUNT / (DIMENTION_COUNT + COLOR_COUNT)];
    GLuint VBO[PROPERTIES_MAX_COUNT / (DIMENTION_COUNT + COLOR_COUNT)];
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
        shapes[i].color = circle.color;

        prevPoint = newPoint;
    }

    drawShapeArray(shapes, STEPS + 1, shaderProgram);

    for (int i = 0; i <= STEPS; i++) {
        free(shapes[i].vertices);
    }
}