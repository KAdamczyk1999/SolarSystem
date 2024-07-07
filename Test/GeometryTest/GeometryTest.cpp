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
