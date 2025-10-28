#include "triangle.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(TriangleTest, DefaultConstructor) {
  Triangle t;
  EXPECT_NO_THROW(t.getCenter());
  EXPECT_GT(t.getArea(), 0.0);
}

TEST(TriangleTest, ParameterizedConstructor) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t(p1, p2, p3);

  const auto& vertices = t.getVertices();
  EXPECT_EQ(vertices[0], p1);
  EXPECT_EQ(vertices[1], p2);
  EXPECT_EQ(vertices[2], p3);
}

TEST(TriangleTest, CopyConstructor) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2(t1);

  EXPECT_EQ(t1, t2);
}

TEST(TriangleTest, MoveConstructor) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2(std::move(t1));

  EXPECT_EQ(t2.getVertices()[0], p1);
}

TEST(TriangleTest, CopyAssignment) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2;
  t2 = t1;

  EXPECT_EQ(t1, t2);
}

TEST(TriangleTest, MoveAssignment) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2;
  t2 = std::move(t1);

  EXPECT_EQ(t2.getVertices()[0], p1);
}

TEST(TriangleTest, Equality) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2(p1, p2, p3);

  EXPECT_TRUE(t1 == t2);
  EXPECT_TRUE(t1.isEqual(t2));
}

TEST(TriangleTest, Inequality) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);
  Triangle t2(Point(0, 0), Point(5, 0), Point(2, 4));

  EXPECT_FALSE(t1 == t2);
  EXPECT_FALSE(t1.isEqual(t2));
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

  double area = t.getArea();
  EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(TriangleTest, GetAreaRightTriangle) {
  Point p1(0, 0);
  Point p2(3, 0);
  Point p3(0, 4);
  Triangle t(p1, p2, p3);

  double area = t.getArea();
  EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(TriangleTest, OperatorDouble) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(0, 3);
  Triangle t(p1, p2, p3);

  double area = static_cast<double>(t);
  EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(TriangleTest, Print) {
  Point p1(1, 2);
  Point p2(3, 4);
  Point p3(5, 6);
  Triangle t(p1, p2, p3);

  std::ostringstream oss;
  oss << t;

  std::string output = oss.str();
  EXPECT_TRUE(output.find("Triangle") != std::string::npos);
  EXPECT_TRUE(output.find("1") != std::string::npos);
  EXPECT_TRUE(output.find("2") != std::string::npos);
}

TEST(TriangleTest, Read) {
  std::istringstream iss("1 2 3 4 5 6");
  Triangle t;
  iss >> t;

  const auto& vertices = t.getVertices();
  EXPECT_NEAR(vertices[0].x, 1.0, 1e-9);
  EXPECT_NEAR(vertices[0].y, 2.0, 1e-9);
  EXPECT_NEAR(vertices[1].x, 3.0, 1e-9);
  EXPECT_NEAR(vertices[1].y, 4.0, 1e-9);
  EXPECT_NEAR(vertices[2].x, 5.0, 1e-9);
  EXPECT_NEAR(vertices[2].y, 6.0, 1e-9);
}

TEST(TriangleTest, Clone) {
  Point p1(0, 0);
  Point p2(4, 0);
  Point p3(2, 3);
  Triangle t1(p1, p2, p3);

  auto cloned = t1.clone();
  EXPECT_TRUE(t1.isEqual(*cloned));
}
