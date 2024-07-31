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

#define ASTEROID_GROUP_COUNT 500
#define ASTEROID_GROUP_SIZE 3
typedef struct {
    Point coords[ASTEROID_GROUP_SIZE];
    float angularSpeeds[ASTEROID_GROUP_SIZE];
} AsteroidGroupParams;

AsteroidGroupParams asteroidGroupParams[ASTEROID_GROUP_COUNT];
Shape asteroidPairs[ASTEROID_GROUP_COUNT];

void generateAsteroids() {
    for (int i = 0; i < ASTEROID_GROUP_COUNT; i++) {
        for (int j = 0; j < ASTEROID_GROUP_SIZE; j++) {
            float angle = rand() / (RAND_MAX / (2 * PI));
            float proximity = rand() / (RAND_MAX / 0.025f) + 0.22f;
            asteroidGroupParams[i].coords[j].x = cos(angle) * proximity;
            asteroidGroupParams[i].coords[j].y = sin(angle) * proximity;
            asteroidGroupParams[i].coords[j].z = 0.0f;
            asteroidGroupParams[i].angularSpeeds[j] = rand() / (RAND_MAX / .5f);
        }
        asteroidPairs[i].vertices = asteroidGroupParams[i].coords;
        asteroidPairs[i].verticesCount = ASTEROID_GROUP_SIZE;
        asteroidPairs[i].drawingMethod = GL_POINTS;
    }
}