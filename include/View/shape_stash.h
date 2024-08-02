#pragma once
#include <stdlib.h>

#include "Geometry/shapes.h"

#define PLANET_COUNT 8

Circle sun = {{0.0f, 0.0f, 0.0f}, 0.06f, {1.0f, 1.0f, 1.0f}};

typedef struct {
    Circle circle;
    float angularSpeed;
} Satelite;

Satelite planets[PLANET_COUNT] = {
    {{{0.0f, 0.07f, 0.0f}, 0.0050f, {0.6f, 0.6f, 0.6f}}, 8.264E000f},  // MERCURY
    {{{0.0f, 0.10f, 0.0f}, 0.0150f, {0.8f, 0.4f, 0.0f}}, 3.232E000f},  // VENUS
    {{{0.0f, 0.14f, 0.0f}, 0.0150f, {0.0f, 0.5f, 1.0f}}, 1.992E000f},  // EARTH
    {{{0.0f, 0.20f, 0.0f}, 0.0075f, {1.0f, 0.0f, 0.0f}}, 1.059E000f},  // MARS
    {{{0.0f, 0.30f, 0.0f}, 0.0300f, {1.0f, 0.7f, 0.3f}}, 1.673E-01f},  // JUPITER
    {{{0.0f, 0.50f, 0.0f}, 0.0250f, {1.0f, 0.8f, 0.7f}}, 9.294E-02f},  // SATURN
    {{{0.0f, 0.70f, 0.0f}, 0.0200f, {0.0f, 0.7f, 1.0f}}, 2.370E-02f},  // URANUS
    {{{0.0f, 0.90f, 0.0f}, 0.0200f, {0.0f, 0.3f, 1.0f}}, 1.208E-02f},  // NEPTUNE
};

#define ASTEROID_COUNT 300
struct {
    Point coords[ASTEROID_COUNT];
    Shape shape;
    float angularSpeeds[ASTEROID_COUNT];
} asteroids;

#define SATURN_RING_ELEMENTS_COUNT 500
struct {
    Point coords[SATURN_RING_ELEMENTS_COUNT];
    Shape shape;
    float angularSpeeds[SATURN_RING_ELEMENTS_COUNT];
} saturnRing;

void _generateAsteroid(Point* coords, Shape* shape, float* angularSpeed, float minProximity, float band,
                       Point centerPoint) {
    float angle = rand() / (RAND_MAX / (2 * PI));
    float proximity = rand() / (RAND_MAX / band) + minProximity;
    coords->x = cos(angle) * proximity + centerPoint.x;
    coords->y = sin(angle) * proximity + centerPoint.y;
    coords->z = 0.0f;
    *angularSpeed = rand() / (RAND_MAX / .5f);
}

void _assignAsteroidProperties(Shape* shape, Point* coords, Color color, int count) {
    shape->vertices = coords;
    shape->verticesCount = count;
    shape->drawingMethod = GL_POINTS;
    shape->color.r = color.r;
    shape->color.g = color.g;
    shape->color.b = color.b;
}

void _generateAsteroids(Shape* shape, Point* coords, Color color, float* angularSpeeds, int count, float minProximity,
                        float band, Point centerPoint) {
    for (int i = 0; i < count; i++) {
        _generateAsteroid(&(coords[i]), shape, &(angularSpeeds[i]), minProximity, band, centerPoint);
    }

    _assignAsteroidProperties(shape, coords, color, count);
}

#define SATURN planets[5]
void generateAllAsteroids() {
    _generateAsteroids(&asteroids.shape, asteroids.coords, (Color){.3f, .3f, .3f}, asteroids.angularSpeeds,
                       ASTEROID_COUNT, .22f, .025f, sun.centerPoint);
    _generateAsteroids(&saturnRing.shape, saturnRing.coords, (Color){1.0f, 0.8f, 0.7f}, saturnRing.angularSpeeds,
                       SATURN_RING_ELEMENTS_COUNT, SATURN.circle.radius + 0.01f, 0.02f, SATURN.circle.centerPoint);
}

#define STAR_COUNT 200
struct {
    Point coords[STAR_COUNT];
    Shape shape;
} stars;

void generateStars() {
    stars.shape.color = (Color){1.0f, 1.0f, 1.0f};
    stars.shape.vertices = stars.coords;
    stars.shape.verticesCount = STAR_COUNT;
    stars.shape.drawingMethod = GL_POINTS;

    for (int i = 0; i < STAR_COUNT; i++) {
        stars.coords[i].x = rand() / (RAND_MAX / 2.0f) - 1.0f;
        stars.coords[i].y = rand() / (RAND_MAX / 2.0f) - 1.0f;
        stars.coords[i].z = 0;
    }
}