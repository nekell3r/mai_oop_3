#include "hexagon.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(HexagonTest, DefaultConstructor) {
  Hexagon h;
  EXPECT_NO_THROW(h.getCenter());
  EXPECT_GT(h.getArea(), 0.0);
}

TEST(HexagonTest, ParameterizedConstructor) {
  Point p1(1, 0);
  Point p2(0.5, std::sqrt(3) / 2);
  Point p3(-0.5, std::sqrt(3) / 2);
  Point p4(-1, 0);
  Point p5(-0.5, -std::sqrt(3) / 2);
  Point p6(0.5, -std::sqrt(3) / 2);
  Hexagon h(p1, p2, p3, p4, p5, p6);

  const auto& vertices = h.getVertices();
  EXPECT_EQ(vertices[0], p1);
  EXPECT_EQ(vertices[1], p2);
}

TEST(HexagonTest, CopyConstructor) {
  Hexagon h1;
  Hexagon h2(h1);

  EXPECT_EQ(h1, h2);
}

TEST(HexagonTest, MoveConstructor) {
  Hexagon h1;
  auto originalCenter = h1.getCenter();
  Hexagon h2(std::move(h1));

  EXPECT_NEAR(h2.getCenter().x, originalCenter.x, 1e-9);
  EXPECT_NEAR(h2.getCenter().y, originalCenter.y, 1e-9);
}

TEST(HexagonTest, CopyAssignment) {
  Hexagon h1;
  Hexagon h2;
  h2 = h1;

  EXPECT_EQ(h1, h2);
}

TEST(HexagonTest, MoveAssignment) {
  Hexagon h1;
  auto originalArea = h1.getArea();
  Hexagon h2;
  h2 = std::move(h1);

  EXPECT_NEAR(h2.getArea(), originalArea, 1e-9);
}

TEST(HexagonTest, Equality) {
  Point p1(1, 0);
  Point p2(0.5, std::sqrt(3) / 2);
  Point p3(-0.5, std::sqrt(3) / 2);
  Point p4(-1, 0);
  Point p5(-0.5, -std::sqrt(3) / 2);
  Point p6(0.5, -std::sqrt(3) / 2);
  Hexagon h1(p1, p2, p3, p4, p5, p6);
  Hexagon h2(p1, p2, p3, p4, p5, p6);

  EXPECT_TRUE(h1 == h2);
  EXPECT_TRUE(h1.isEqual(h2));
}

TEST(HexagonTest, Inequality) {
  Hexagon h1;
  Point p1(2, 0);
  Point p2(1, std::sqrt(3));
  Point p3(-1, std::sqrt(3));
  Point p4(-2, 0);
  Point p5(-1, -std::sqrt(3));
  Point p6(1, -std::sqrt(3));
  Hexagon h2(p1, p2, p3, p4, p5, p6);

  EXPECT_FALSE(h1 == h2);
  EXPECT_FALSE(h1.isEqual(h2));
}

TEST(HexagonTest, GetCenterRegular) {
  Hexagon h;
  Point center = h.getCenter();

  // Правильный шестиугольник с центром в (0, 0)
  EXPECT_NEAR(center.x, 0.0, 1e-9);
  EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST(HexagonTest, GetArea) {
  // Правильный шестиугольник с радиусом 1
  Hexagon h;
  double area = h.getArea();

  // Площадь правильного шестиугольника: (3√3/2) * r^2
  double expectedArea = (3.0 * std::sqrt(3.0) / 2.0) * 1.0 * 1.0;
  EXPECT_NEAR(area, expectedArea, 1e-6);
}

TEST(HexagonTest, GetAreaSimple) {
  // Шестиугольник с вершинами формирующими простую фигуру
  Point p1(1, 0);
  Point p2(2, 0);
  Point p3(2, 1);
  Point p4(1, 1);
  Point p5(0, 1);
  Point p6(0, 0);
  Hexagon h(p1, p2, p3, p4, p5, p6);

  double area = h.getArea();
  EXPECT_GT(area, 0.0);
}

TEST(HexagonTest, OperatorDouble) {
  Hexagon h;
  double area = static_cast<double>(h);

  EXPECT_NEAR(area, h.getArea(), 1e-9);
}

TEST(HexagonTest, Print) {
  Hexagon h;
  std::ostringstream oss;
  oss << h;

  std::string output = oss.str();
  EXPECT_TRUE(output.find("Hexagon") != std::string::npos);
}

TEST(HexagonTest, Read) {
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12");
  Hexagon h;
  iss >> h;

  const auto& vertices = h.getVertices();
  EXPECT_NEAR(vertices[0].x, 1.0, 1e-9);
  EXPECT_NEAR(vertices[0].y, 2.0, 1e-9);
  EXPECT_NEAR(vertices[5].x, 11.0, 1e-9);
  EXPECT_NEAR(vertices[5].y, 12.0, 1e-9);
}

TEST(HexagonTest, Clone) {
  Hexagon h1;
  auto cloned = h1.clone();

  EXPECT_TRUE(h1.isEqual(*cloned));
}
