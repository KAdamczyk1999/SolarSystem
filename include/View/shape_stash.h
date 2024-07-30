#pragma once
#include <stdlib.h>

#include "Geometry/shapes.h"

#define SHAPE_COUNT 8

Circle sun = {{0.0f, 0.0f, 0.0f}, 0.06f};

Circle planets[SHAPE_COUNT] = {
    {{0.0f, 0.07f, 0.0f}, 0.0050f}, {{0.0f, 0.1f, 0.0f}, 0.0150f},  {{0.0f, 0.14f, 0.0f}, 0.0150f},
    {{0.0f, 0.20f, 0.0f}, 0.0075f}, {{0.0f, 0.30f, 0.0f}, 0.0300f}, {{0.0f, 0.50f, 0.0f}, 0.0250f},
    {{0.0f, 0.70f, 0.0f}, 0.0200f}, {{0.0f, 0.90f, 0.0f}, 0.0200f},
};

float angularSpeeds[SHAPE_COUNT] = {8.264E0f,   3.232E0f,  1.992E0f,  1.059E0f,
                                    1.673E-01f, 9.294E-02, 2.370E-02, 1.208E-02};