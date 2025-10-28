#include "octagon.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(OctagonTest, DefaultConstructor) {
  Octagon o;
  EXPECT_NO_THROW(o.getCenter());
  EXPECT_GT(o.getArea(), 0.0);
}

TEST(OctagonTest, ParameterizedConstructor) {
  Point p1(1, 0);
  Point p2(std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p3(0, 1);
  Point p4(-std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p5(-1, 0);
  Point p6(-std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Point p7(0, -1);
  Point p8(std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Octagon o(p1, p2, p3, p4, p5, p6, p7, p8);

  const auto& vertices = o.getVertices();
  EXPECT_EQ(vertices[0], p1);
  EXPECT_EQ(vertices[2], p3);
}

TEST(OctagonTest, CopyConstructor) {
  Octagon o1;
  Octagon o2(o1);

  EXPECT_EQ(o1, o2);
}

TEST(OctagonTest, MoveConstructor) {
  Octagon o1;
  auto originalCenter = o1.getCenter();
  Octagon o2(std::move(o1));

  EXPECT_NEAR(o2.getCenter().x, originalCenter.x, 1e-9);
  EXPECT_NEAR(o2.getCenter().y, originalCenter.y, 1e-9);
}

TEST(OctagonTest, CopyAssignment) {
  Octagon o1;
  Octagon o2;
  o2 = o1;

  EXPECT_EQ(o1, o2);
}

TEST(OctagonTest, MoveAssignment) {
  Octagon o1;
  auto originalArea = o1.getArea();
  Octagon o2;
  o2 = std::move(o1);

  EXPECT_NEAR(o2.getArea(), originalArea, 1e-9);
}

TEST(OctagonTest, Equality) {
  Point p1(1, 0);
  Point p2(std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p3(0, 1);
  Point p4(-std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p5(-1, 0);
  Point p6(-std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Point p7(0, -1);
  Point p8(std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Octagon o1(p1, p2, p3, p4, p5, p6, p7, p8);
  Octagon o2(p1, p2, p3, p4, p5, p6, p7, p8);

  EXPECT_TRUE(o1 == o2);
  EXPECT_TRUE(o1.isEqual(o2));
}

TEST(OctagonTest, Inequality) {
  Octagon o1;
  Point p1(2, 0);
  Point p2(std::sqrt(2), std::sqrt(2));
  Point p3(0, 2);
  Point p4(-std::sqrt(2), std::sqrt(2));
  Point p5(-2, 0);
  Point p6(-std::sqrt(2), -std::sqrt(2));
  Point p7(0, -2);
  Point p8(std::sqrt(2), -std::sqrt(2));
  Octagon o2(p1, p2, p3, p4, p5, p6, p7, p8);

  EXPECT_FALSE(o1 == o2);
  EXPECT_FALSE(o1.isEqual(o2));
}

TEST(OctagonTest, GetCenterRegular) {
  Octagon o;
  Point center = o.getCenter();

  // Правильный восьмиугольник с центром в (0, 0)
  EXPECT_NEAR(center.x, 0.0, 1e-9);
  EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST(OctagonTest, GetArea) {
  // Правильный восьмиугольник с радиусом 1
  Octagon o;
  double area = o.getArea();

  // Площадь правильного восьмиугольника с радиусом описанной окружности r: 2 * r^2 * √2
  double expectedArea = 2.0 * 1.0 * 1.0 * std::sqrt(2.0);
  EXPECT_NEAR(area, expectedArea, 1e-6);
}

TEST(OctagonTest, GetAreaSimple) {
  // Восьмиугольник с вершинами формирующими простую фигуру
  Point p1(1, 0);
  Point p2(1, 1);
  Point p3(0, 1);
  Point p4(-1, 1);
  Point p5(-1, 0);
  Point p6(-1, -1);
  Point p7(0, -1);
  Point p8(1, -1);
  Octagon o(p1, p2, p3, p4, p5, p6, p7, p8);

  double area = o.getArea();
  EXPECT_GT(area, 0.0);
}

TEST(OctagonTest, OperatorDouble) {
  Octagon o;
  double area = static_cast<double>(o);

  EXPECT_NEAR(area, o.getArea(), 1e-9);
}

TEST(OctagonTest, Print) {
  Octagon o;
  std::ostringstream oss;
  oss << o;

  std::string output = oss.str();
  EXPECT_TRUE(output.find("Octagon") != std::string::npos);
}

TEST(OctagonTest, Read) {
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  Octagon o;
  iss >> o;

  const auto& vertices = o.getVertices();
  EXPECT_NEAR(vertices[0].x, 1.0, 1e-9);
  EXPECT_NEAR(vertices[0].y, 2.0, 1e-9);
  EXPECT_NEAR(vertices[7].x, 15.0, 1e-9);
  EXPECT_NEAR(vertices[7].y, 16.0, 1e-9);
}

TEST(OctagonTest, Clone) {
  Octagon o1;
  auto cloned = o1.clone();

  EXPECT_TRUE(o1.isEqual(*cloned));
}
