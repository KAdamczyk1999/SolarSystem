#include "View/main_view.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Geometry/shapes.h"
#include "View/shaders.h"

const int dimentions = 3;
Triangle myShapes[] = {{{-.25f, 0.5f}, {0.0f, .75f}, {.25f, 0.5f}}, {{-.25f, -0.25f}, {0.0f, -.0f}, {.25f, -0.25f}}};
GLuint shaderProgram;
GLuint VAO, VBO;
void _setUpVertexObjects() {
    int shapeCount = sizeof(myShapes) / sizeof(myShapes[0]);
    glGenVertexArrays(shapeCount, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    for (int i = 0; i < shapeCount; i++) {
        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        GLfloat* shapeVertices = malloc(shapeVerticesCount * dimentions * sizeof(GLfloat));
        mapShapeToGLVertices(myShapes[i], shapeVertices, shapeVerticesCount, 2);

        glBufferData(GL_ARRAY_BUFFER, shapeVerticesCount * dimentions * sizeof(GLfloat), shapeVertices,
                     GL_DYNAMIC_DRAW);

        glVertexAttribPointer(i, shapeVerticesCount, GL_FLOAT, GL_FALSE, shapeVerticesCount * sizeof(GLfloat),
                              (void*)0);
        glEnableVertexAttribArray(i);

        free(shapeVertices);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    for (int i = 0; i < shapeCount; i++) {
        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        glDrawArrays(GL_TRIANGLES, i, shapeVerticesCount);
    }
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
    _setUpVertexObjects();

    int shapeCount = sizeof(myShapes) / sizeof(myShapes[0]);
    for (int i = 0; i < shapeCount; i++) {
        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        rotateShape(myShapes[i], shapeVerticesCount, 1.0f * (pow(-1.0, i)), pointOfRotation);
    }
}

void runOnExit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}