#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define PI 3.141592654

typedef struct {
    float x;
    float y;
} Point;

typedef Point Triangle[3];

void rotateShape(Point* shape, int verticesCount, float angleDegs, Point pointOfRotation);

#ifdef __cplusplus
}
#endif