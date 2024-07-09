#include "View/main_view.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Geometry/shapes.h"
#include "View/shaders.h"

const int dimentions = 3;
Triangle myShape = {{-.25f, 0.0f}, {0.0f, .25f}, {.25f, 0.0f}};
GLuint shaderProgram;
GLuint VAO, VBO;
void _setUpVertexObjects(GLfloat* shapeVertices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int shapeVerticesCount = sizeof(myShape) / sizeof(myShape[0]);
    glBufferData(GL_ARRAY_BUFFER, shapeVerticesCount * dimentions * sizeof(GLfloat), shapeVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, shapeVerticesCount * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void runOnEntry() {
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

Point pointOfRotation = {.0f, -.2f};
void runMainLoop() {
    int shapeVerticesCount = sizeof(myShape) / sizeof(myShape[0]);
    GLfloat* myShapeVertices = malloc(shapeVerticesCount * dimentions * sizeof(GLfloat));
    mapShapeToGLVertices(myShape, myShapeVertices, shapeVerticesCount);

    _setUpVertexObjects(myShapeVertices);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, shapeVerticesCount);

    rotateShape(myShape, shapeVerticesCount, 1.0f, pointOfRotation);

    free(myShapeVertices);
}

void runOnExit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}