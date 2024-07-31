#include "View/main_view.h"

#include <math.h>

#include "View/drawer.h"
#include "View/shaders.h"
#include "View/shape_stash.h"

GLuint shaderProgram;

void runOnEntry() {
    generateAsteroids();
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

void _rotateObjects(Point pointOfRotation) {
    for (int i = 0; i < PLANET_COUNT; i++)
        rotatePoint(&(planets[i].circle.centerPoint), planets[i].angularSpeed, pointOfRotation);
    for (int i = 0; i < ASTEROID_COUNT; i++)
        rotatePoint(&(asteroids.coords[i]), asteroids.angularSpeeds[i], pointOfRotation);
    for (int i = 0; i < SATURN_RING_ELEMENTS_COUNT; i++)
        rotatePoint(&(saturnRing.coords[i]), SATURN.angularSpeed, pointOfRotation);
    for (int i = 0; i < SATURN_RING_ELEMENTS_COUNT; i++)
        rotatePoint(&(saturnRing.coords[i]), saturnRing.angularSpeeds[i], SATURN.circle.centerPoint);
}

void runMainLoop() {
    for (int i = 0; i < PLANET_COUNT; i++) drawCircle(planets[i].circle, shaderProgram);
    drawCircle(sun, shaderProgram);

    drawShapeArray(asteroids.shapes, ASTEROID_COUNT, shaderProgram);
    drawShapeArray(saturnRing.shapes, SATURN_RING_ELEMENTS_COUNT, shaderProgram);

    _rotateObjects(sun.centerPoint);
}

void runOnExit() { glDeleteProgram(shaderProgram); }