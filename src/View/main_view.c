#include "View/main_view.h"

#include <math.h>

#include "View/drawer.h"
#include "View/shaders.h"
#include "View/shape_stash.h"

GLuint shaderProgram;

void runOnEntry() {
    createSatelites();

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

void _rotateShapes(Point pointOfRotation) {
    for (int i = 0; i < SHAPE_COUNT; i++) {
        rotateShape(&(satelites[i]), (SHAPE_COUNT - i + 1) * 2.0f * (pow(-1.0, i)), getShapeCenter(satelites[i]));
        rotateShape(&(satelites[i]), (SHAPE_COUNT - i + 1) * .3f * (pow(-1.0, i)), pointOfRotation);
    }
}

void runMainLoop() {
    drawShapeArray(satelites, SHAPE_COUNT, shaderProgram);

    Circle circle = {{0.0f, 0.0f, 0.0f}, 0.06f};
    drawCircle(circle, shaderProgram);
    _rotateShapes(circle.centerPoint);
}

void runOnExit() { glDeleteProgram(shaderProgram); }