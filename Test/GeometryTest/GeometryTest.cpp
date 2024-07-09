#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "shapes.h"

using namespace testing;

struct GeometryShould : public Test {
    void SetUp() {}
};

TEST_F(GeometryShould, rotateShapeProperly) {
    Triangle triangle = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
    Triangle triangle2 = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
    Point rotationPoint = {1.0f, 1.0f};
    int triangleSize = sizeof(triangle) / sizeof(triangle[0]);
    rotateShape(triangle, triangleSize, 10.0f, rotationPoint);
    rotateShape(triangle2, triangleSize, 370.0f, rotationPoint);
    for (int i = 0; i < triangleSize; i++) {
        EXPECT_NEAR(triangle[i].x, triangle2[i].x, 0.000001);
        EXPECT_NEAR(triangle[i].y, triangle2[i].y, 0.000001);
    }
}

TEST_F(GeometryShould, convertShapeToVerticesAllDimenstion) {
    Point shape[3][3] = {{{0.0f}, {1.0f}, {2.0f}},
                         {{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}},
                         {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {2.0f, 0.0f, 2.0f}}};
    int shapeVerticesCount = sizeof(shape[0]) / sizeof(shape[0][0]);
    GLfloat* shapeVertices = (GLfloat*)malloc(shapeVerticesCount * 3 * sizeof(GLfloat));
    for (int dim = 1; dim <= 3; dim++) {
        mapShapeToGLVertices(shape[dim - 1], shapeVertices, shapeVerticesCount, dim);

        for (int j = 0; j < shapeVerticesCount; j++) {
            EXPECT_NEAR(shape[dim - 1][j].x, shapeVertices[j * 3], 0.000001);
            EXPECT_NEAR(shape[dim - 1][j].y, shapeVertices[j * 3 + 1], 0.000001);
            EXPECT_NEAR(shape[dim - 1][j].z, shapeVertices[j * 3 + 2], 0.000001);
        }
    }
    free(shapeVertices);
}

TEST_F(GeometryShould, dieIfWrongDimensionInShapeConversion) {
    Triangle shape = {{0.0f}, {1.0f}, {2.0f}};
    int shapeVerticesCount = sizeof(shape) / sizeof(shape[0]);
    GLfloat* shapeVertices = (GLfloat*)malloc(shapeVerticesCount * 3 * sizeof(GLfloat));
    EXPECT_DEATH(mapShapeToGLVertices(shape, shapeVertices, shapeVerticesCount, 4), "");
    free(shapeVertices);
}