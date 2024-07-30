#include "View/main_view.h"

#include <math.h>

#include "View/drawer.h"
#include "View/shaders.h"
#include "View/shape_stash.h"

GLuint shaderProgram;

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

void _rotatePlanets(Point pointOfRotation) {
    for (int i = 0; i < SHAPE_COUNT; i++) rotatePoint(&(planets[i].centerPoint), angularSpeeds[i], pointOfRotation);
}

void runMainLoop() {
    for (int i = 0; i < SHAPE_COUNT; i++) drawCircle(planets[i], shaderProgram);

    Circle sun = {{0.0f, 0.0f, 0.0f}, 0.06f};
    drawCircle(sun, shaderProgram);
    _rotatePlanets(sun.centerPoint);
}

void runOnExit() { glDeleteProgram(shaderProgram); }