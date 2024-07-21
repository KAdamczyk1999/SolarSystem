#include "View/main_view.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Geometry/shapes.h"
#include "View/shaders.h"
#include "View/shape_stash.h"

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

void _drawShape(Shape shape, int shapeIndex, GLuint* VAO, GLuint* VBO) {
    glBindVertexArray(VAO[shapeIndex]);
    glDrawArrays(shape.drawingMethod, 0, shape.verticesCount);
}

GLuint shaderProgram;
GLuint VAO[SHAPE_COUNT];
GLuint VBO[SHAPE_COUNT];
void _setUpVertexObjects() {
    glGenVertexArrays(SHAPE_COUNT, VAO);
    glGenBuffers(SHAPE_COUNT, VBO);

    for (int i = 0; i < SHAPE_COUNT; i++) {
        _setUpShape(myShapes[i], i, VAO, VBO);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    for (int i = 0; i < SHAPE_COUNT; i++) {
        _drawShape(myShapes[i], i, VAO, VBO);
    }
    glUseProgram(0);
}

void _setUpCircle(Point point, float radius) {
#define STEPS 200
    GLuint cVAO[STEPS + 1];
    GLuint cVBO[STEPS + 1];
    Shape shapes[STEPS + 1];
    glGenVertexArrays(STEPS + 1, cVAO);
    glGenBuffers(STEPS + 1, cVBO);
    const float angle = PI * 2.0f / STEPS;
    float prevX = point.x;
    float prevY = point.y - radius;

    for (int i = 0; i <= STEPS; i++) {
        float newX = radius * sin(angle * i);
        float newY = -radius * cos(angle * i);

        Point shapeVertices[3] = {point, {prevX, prevY, 0.0f}, {newX, newY, 0.0f}};
        shapes[i].vertices = shapeVertices;
        shapes[i].verticesCount = 3;
        shapes[i].drawingMethod = GL_TRIANGLES;

        _setUpShape(shapes[i], i, cVAO, cVBO);

        prevX = newX;
        prevY = newY;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    for (int i = 0; i <= STEPS; i++) {
        _drawShape(shapes[i], i, cVAO, cVBO);
    }
    glUseProgram(0);
}
void runOnEntry() {
    createShapes();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Point pointOfRotation = {0.0f, 0.0f, 0.0f};
void _rotateShapes() {
    for (int i = 0; i < SHAPE_COUNT; i++) {
        rotateShape(myShapes[i], i * 2.0f * (pow(-1.0, i)), getShapeCenter(myShapes[i]));
        rotateShape(myShapes[i], 1.0f * (pow(-1.0, i)), pointOfRotation);
    }
}

void runMainLoop() {
    _setUpVertexObjects();
    _setUpCircle(pointOfRotation, .03f);
    _rotateShapes();
}

void runOnExit() {
    glDeleteVertexArrays(SHAPE_COUNT, VAO);
    glDeleteBuffers(SHAPE_COUNT, VBO);
    glDeleteProgram(shaderProgram);
    for (int i = 0; i < SHAPE_COUNT; i++) {
        free(triangleVerticesTab[i]);
    }
}