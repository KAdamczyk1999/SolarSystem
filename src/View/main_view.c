#include "View/main_view.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Geometry/shapes.h"

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader source code
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

GLuint shaderProgram;
void _prepareShaders() {
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

GLuint VAO, VBO;
GLfloat* myShapeVertices;
int myShapeVerticesCount;
void _setUpVertexObjects() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, myShapeVerticesCount * 3 * sizeof(GLfloat), myShapeVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, myShapeVerticesCount * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Triangle myShape;
void runOnEntry() {
    float triangleShape[3][2] = {{-.25f, 0.0f}, {0.0f, .25f}, {.25f, 0.0f}};
    memcpy(myShape, triangleShape, 6 * sizeof(float));
    myShapeVerticesCount = sizeof(myShape) / sizeof(myShape[0]);
    myShapeVertices = malloc(myShapeVerticesCount * 3 * sizeof(GLfloat));
    mapShapeToGLVertices(myShape, myShapeVertices, myShapeVerticesCount);

    _prepareShaders();

    _setUpVertexObjects();
}

void runMainLoop() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    Point pointOfRotation = {0.0f, 0.0f};
    rotateShape(myShape, 3, 1.0f, pointOfRotation);
    mapShapeToGLVertices(myShape, myShapeVertices, 3);

    _setUpVertexObjects();
}

void runOnExit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}