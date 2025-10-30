#include "octagon.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(OctagonTest, DefaultConstructor) {
  Octagon o;
  EXPECT_GT(o.getArea(), 0.0);
}

TEST(OctagonTest, GetCenter) {
  Octagon o;
  Point center = o.getCenter();
  
  EXPECT_NEAR(center.x, 0.0, 1e-9);
  EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST(OctagonTest, GetArea) {
  Octagon o;
  double area = o.getArea();
  
  double expectedArea = 2.0 * 1.0 * 1.0 * std::sqrt(2.0);
  EXPECT_NEAR(area, expectedArea, 1e-6);
}

TEST(OctagonTest, Equality) {
  Point p1(1, 0), p2(std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p3(0, 1), p4(-std::sqrt(2) / 2, std::sqrt(2) / 2);
  Point p5(-1, 0), p6(-std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Point p7(0, -1), p8(std::sqrt(2) / 2, -std::sqrt(2) / 2);
  
  Octagon o1(p1, p2, p3, p4, p5, p6, p7, p8);
  Octagon o2(p1, p2, p3, p4, p5, p6, p7, p8);
  
  EXPECT_TRUE(o1 == o2);
}

TEST(OctagonTest, Print) {
  Octagon o;
  std::ostringstream oss;
  oss << o;
  
  EXPECT_TRUE(oss.str().find("Octagon") != std::string::npos);
}

TEST(OctagonTest, Read) {
  std::istringstream iss("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
  Octagon o;
  iss >> o;
  
  EXPECT_NEAR(o.getVertices()[0].x, 1.0, 1e-9);
  EXPECT_NEAR(o.getVertices()[7].y, 16.0, 1e-9);
}
