#include "triangle.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(TriangleTest, DefaultConstructor) {
  Triangle t;
  EXPECT_GT(t.getArea(), 0.0);
}

TEST(TriangleTest, ParameterizedConstructor) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t(p1, p2, p3);
  
  EXPECT_EQ(t.getVertices()[0], p1);
  EXPECT_EQ(t.getVertices()[1], p2);
  EXPECT_EQ(t.getVertices()[2], p3);
}

TEST(TriangleTest, GetCenter) {
  Point p1(0, 0);
  Point p2(6, 0);
  Point p3(3, 6);
  Triangle t(p1, p2, p3);
  
  Point center = t.getCenter();
  EXPECT_NEAR(center.x, 3.0, 1e-9);
  EXPECT_NEAR(center.y, 2.0, 1e-9);
}

TEST(TriangleTest, GetArea) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(0, 3);
  Triangle t(p1, p2, p3);
  
  EXPECT_NEAR(t.getArea(), 6.0, 1e-9);
}

TEST(TriangleTest, Equality) {
  Triangle t1(Point(0, 0), Point(4, 0), Point(2, 3));
  Triangle t2(Point(0, 0), Point(4, 0), Point(2, 3));
  
  EXPECT_TRUE(t1 == t2);
}

TEST(TriangleTest, Print) {
  Triangle t(Point(1, 2), Point(3, 4), Point(5, 6));
  
  std::ostringstream oss;
  oss << t;
  
  EXPECT_TRUE(oss.str().find("Triangle") != std::string::npos);
}

TEST(TriangleTest, ReadWrite) {
  std::istringstream iss("1 2 3 4 5 6");
  Triangle t;
  iss >> t;
  
  EXPECT_NEAR(t.getVertices()[0].x, 1.0, 1e-9);
  EXPECT_NEAR(t.getVertices()[2].y, 6.0, 1e-9);
}

TEST(TriangleTest, Clone) {
  Triangle t1(Point(0, 0), Point(4, 0), Point(2, 3));
  auto cloned = t1.clone();
  
  EXPECT_TRUE(t1.isEqual(*cloned));
}
