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

        float verticesCount = myShapes[i].verticesCount;

        GLfloat* shapeVertices = malloc(verticesCount * dimentions * sizeof(GLfloat));
        mapShapeToGLVertices(myShapes[i], shapeVertices, 2);

        glBufferData(GL_ARRAY_BUFFER, verticesCount * dimentions * sizeof(GLfloat), shapeVertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, verticesCount, GL_FLOAT, GL_FALSE, verticesCount * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        free(shapeVertices);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    for (int i = 0; i < SHAPE_COUNT; i++) {
        glBindVertexArray(VAO[i]);
        glDrawArrays(myShapes[i].drawingMethod, 0, myShapes[i].verticesCount);
    }
    glUseProgram(0);
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

void _rotateShapes() {
    Point pointOfRotation = getShapeCenter(myShapes[0]);
    for (int i = 0; i < SHAPE_COUNT; i++) {
        if (i != 0) {
            rotateShape(myShapes[i], i * 2.0f * (pow(-1.0, i)), getShapeCenter(myShapes[i]));
        }
        rotateShape(myShapes[i], 1.0f * (pow(-1.0, i)), pointOfRotation);
    }
}

void runMainLoop() {
    _setUpVertexObjects();
    _rotateShapes();
}

void runOnExit() {
    glDeleteVertexArrays(SHAPE_COUNT, VAO);
    glDeleteBuffers(SHAPE_COUNT, VBO);
    glDeleteProgram(shaderProgram);
}