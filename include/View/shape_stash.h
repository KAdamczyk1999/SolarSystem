#pragma once
#include <stdlib.h>

#include "Geometry/shapes.h"

#define PLANET_COUNT 8

Circle sun = {{0.0f, 0.0f, 0.0f}, 0.06f};

typedef struct {
    Circle circle;
    float angularSpeed;
} Satelite;

Satelite planets[PLANET_COUNT] = {
    {{{0.0f, 0.07f, 0.0f}, 0.0050f}, 8.264E000f}, {{{0.0f, 0.10f, 0.0f}, 0.0150f}, 3.232E000f},
    {{{0.0f, 0.14f, 0.0f}, 0.0150f}, 1.992E000f}, {{{0.0f, 0.20f, 0.0f}, 0.0075f}, 1.059E000f},
    {{{0.0f, 0.30f, 0.0f}, 0.0300f}, 1.673E-01f}, {{{0.0f, 0.50f, 0.0f}, 0.0250f}, 9.294E-02f},
    {{{0.0f, 0.70f, 0.0f}, 0.0200f}, 2.370E-02f}, {{{0.0f, 0.90f, 0.0f}, 0.0200f}, 1.208E-02f},
};

#define ASTEROID_COUNT 500
typedef struct {
    Point coords[ASTEROID_COUNT];
    Shape shapes[ASTEROID_COUNT];
    float angularSpeeds[ASTEROID_COUNT];
} Asteroids;

Asteroids asteroids;

void generateAsteroids() {
    for (int i = 0; i < ASTEROID_COUNT; i++) {
        float angle = rand() / (RAND_MAX / (2 * PI));
        float proximity = rand() / (RAND_MAX / 0.025f) + 0.22f;
        asteroids.coords[i].x = cos(angle) * proximity;
        asteroids.coords[i].y = sin(angle) * proximity;
        asteroids.coords[i].z = 0.0f;
        asteroids.angularSpeeds[i] = rand() / (RAND_MAX / .5f);

        asteroids.shapes[i].vertices = &(asteroids.coords[i]);
        asteroids.shapes[i].verticesCount = 1;
        asteroids.shapes[i].drawingMethod = GL_POINTS;
    }
}