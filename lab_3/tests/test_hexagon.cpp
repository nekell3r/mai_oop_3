#include "hexagon.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using geometry::Hexagon;
using geometry::Point;

TEST(HexagonTest, DefaultConstructor) {
  Hexagon h;
  EXPECT_GT(h.getArea(), 0.0);
}

TEST(HexagonTest, GetCenter) {
  Hexagon h;
  Point center = h.getCenter();
  
  EXPECT_NEAR(center.x, 0.0, 1e-9);
  EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST(HexagonTest, GetArea) {
  Hexagon h;
  double area = h.getArea();
  
  double expectedArea = (3.0 * std::sqrt(3.0) / 2.0) * 1.0 * 1.0;
  EXPECT_NEAR(area, expectedArea, 1e-6);
}

TEST(HexagonTest, Equality) {
  Point p1(1, 0), p2(0.5, std::sqrt(3) / 2), p3(-0.5, std::sqrt(3) / 2);
  Point p4(-1, 0), p5(-0.5, -std::sqrt(3) / 2), p6(0.5, -std::sqrt(3) / 2);
  
  Hexagon h1(p1, p2, p3, p4, p5, p6);
  Hexagon h2(p1, p2, p3, p4, p5, p6);
  
  EXPECT_TRUE(h1 == h2);
}

TEST(HexagonTest, Print) {
  Hexagon h;
  std::ostringstream oss;
  oss << h;
  
  EXPECT_TRUE(oss.str().find("Hexagon") != std::string::npos);
}

TEST(HexagonTest, Read) {
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12");
  Hexagon h;
  iss >> h;
  
  EXPECT_NEAR(h.getVertices()[0].x, 1.0, 1e-9);
  EXPECT_NEAR(h.getVertices()[5].y, 12.0, 1e-9);
}
