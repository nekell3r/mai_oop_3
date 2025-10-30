#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

#include <gtest/gtest.h>
#include <sstream>

using geometry::Array;
using geometry::Triangle;
using geometry::Hexagon;
using geometry::Octagon;
using geometry::Point;

TEST(ArrayTest, AddAndGet) {
  Array arr;
  arr.add(std::make_unique<Triangle>());
  arr.add(std::make_unique<Hexagon>());
  
  EXPECT_EQ(arr.size(), 2);
  EXPECT_NE(arr[0], nullptr);
  EXPECT_NE(arr[1], nullptr);
}

TEST(ArrayTest, AddNullFigureThrows) {
  Array arr;
  EXPECT_THROW(arr.add(nullptr), std::invalid_argument);
}

TEST(ArrayTest, RemoveFigure) {
  Array arr;
  arr.add(std::make_unique<Triangle>());
  arr.add(std::make_unique<Hexagon>());
  
  arr.remove(0);
  EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, GetTotalArea) {
  Array arr;
  
  auto triangle = std::make_unique<Triangle>(Point(0, 0), Point(4, 0), Point(0, 3));
  double area1 = triangle->getArea();
  arr.add(std::move(triangle));
  
  auto hexagon = std::make_unique<Hexagon>();
  double area2 = hexagon->getArea();
  arr.add(std::move(hexagon));
  
  EXPECT_NEAR(arr.getTotalArea(), area1 + area2, 1e-6);
}

TEST(ArrayTest, PrintAll) {
  Array arr;
  arr.add(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0.5, 1)));
  
  std::ostringstream oss;
  arr.printAll(oss);
  
  std::string output = oss.str();
  EXPECT_TRUE(output.find("Figure 0") != std::string::npos);
  EXPECT_TRUE(output.find("Center") != std::string::npos);
}

TEST(ArrayTest, MoveSemantics) {
  Array arr1;
  arr1.add(std::make_unique<Triangle>());
  arr1.add(std::make_unique<Hexagon>());
  
  Array arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 2);
}
