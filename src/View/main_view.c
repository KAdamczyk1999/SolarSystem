#include "View/main_view.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Geometry/shapes.h"
#include "View/shaders.h"
#include "View/shape_stash.h"

const int dimentions = 3;

GLuint shaderProgram;
GLuint VAO[SHAPE_COUNT];
GLuint VBO[SHAPE_COUNT];
void _setUpVertexObjects() {
    glGenVertexArrays(SHAPE_COUNT, VAO);
    glGenBuffers(SHAPE_COUNT, VBO);

    for (int i = 0; i < SHAPE_COUNT; i++) {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);

        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        GLfloat* shapeVertices = malloc(shapeVerticesCount * dimentions * sizeof(GLfloat));
        mapShapeToGLVertices(myShapes[i], shapeVertices, shapeVerticesCount, 2);

        glBufferData(GL_ARRAY_BUFFER, shapeVerticesCount * dimentions * sizeof(GLfloat), shapeVertices,
                     GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, shapeVerticesCount, GL_FLOAT, GL_FALSE, shapeVerticesCount * sizeof(GLfloat),
                              (void*)0);
        glEnableVertexAttribArray(0);

        free(shapeVertices);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for (int i = 0; i < SHAPE_COUNT; i++) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[i]);
        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        glDrawArrays(GL_TRIANGLES, 0, shapeVerticesCount);
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

    for (int i = 0; i < SHAPE_COUNT; i++) {
        int shapeVerticesCount = sizeof(myShapes[i]) / sizeof(myShapes[i][0]);
        rotateShape(myShapes[i], shapeVerticesCount, 1.0f * (pow(-1.0, i)), pointOfRotation);
    }
}

void runOnExit() {
    glDeleteVertexArrays(SHAPE_COUNT, VAO);
    glDeleteBuffers(SHAPE_COUNT, VBO);
    glDeleteProgram(shaderProgram);
}