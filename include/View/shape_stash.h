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

#define ASTEROID_COUNT 1000
struct {
    Point coords[ASTEROID_COUNT];
    Shape shapes[ASTEROID_COUNT];
    float angularSpeeds[ASTEROID_COUNT];
} asteroids;

#define SATURN_RING_ELEMENTS_COUNT 500
struct {
    Point coords[SATURN_RING_ELEMENTS_COUNT];
    Shape shapes[SATURN_RING_ELEMENTS_COUNT];
    float angularSpeeds[SATURN_RING_ELEMENTS_COUNT];
} saturnRing;

void generateAsteroid(Point* coords, Shape* shape, float* angularSpeed, float minProximity, float band,
                      Point centerPoint) {
    float angle = rand() / (RAND_MAX / (2 * PI));
    float proximity = rand() / (RAND_MAX / band) + minProximity;
    coords->x = cos(angle) * proximity + centerPoint.x;
    coords->y = sin(angle) * proximity + centerPoint.y;
    coords->z = 0.0f;
    *angularSpeed = rand() / (RAND_MAX / .5f);

    shape->vertices = coords;
    shape->verticesCount = 1;
    shape->drawingMethod = GL_POINTS;
}

#define SATURN planets[5]
void generateAsteroids() {
    for (int i = 0; i < ASTEROID_COUNT; i++) {
        generateAsteroid(&(asteroids.coords[i]), &(asteroids.shapes[i]), &(asteroids.angularSpeeds[i]), 0.22f, 0.025f,
                         sun.centerPoint);
    }

    for (int i = 0; i < SATURN_RING_ELEMENTS_COUNT; i++) {
        generateAsteroid(&(saturnRing.coords[i]), &(saturnRing.shapes[i]), &(saturnRing.angularSpeeds[i]),
                         SATURN.circle.radius + 0.01, 0.02f, SATURN.circle.centerPoint);
    }
}