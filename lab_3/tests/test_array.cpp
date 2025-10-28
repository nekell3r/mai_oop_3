#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

#include <gtest/gtest.h>
#include <sstream>

using namespace geometry;

TEST(ArrayTest, DefaultConstructor) {
  Array arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, AddFigure) {
  Array arr;
  auto triangle = std::make_unique<Triangle>();
  arr.add(std::move(triangle));

  EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, AddMultipleFigures) {
  Array arr;
  arr.add(std::make_unique<Triangle>());
  arr.add(std::make_unique<Hexagon>());
  arr.add(std::make_unique<Octagon>());

  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, AddNullFigureThrows) {
  Array arr;
  EXPECT_THROW(arr.add(nullptr), std::invalid_argument);
}

TEST(ArrayTest, GetFigure) {
  Array arr;
  auto triangle = std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0.5, 1));
  arr.add(std::move(triangle));

  Figure* fig = arr.get(0);
  EXPECT_NE(fig, nullptr);
  EXPECT_GT(fig->getArea(), 0.0);
}

TEST(ArrayTest, GetInvalidIndexThrows) {
  Array arr;
  arr.add(std::make_unique<Triangle>());

  EXPECT_THROW(arr.get(1), std::out_of_range);
  EXPECT_THROW(arr.get(100), std::out_of_range);
}

TEST(ArrayTest, RemoveFigure) {
  Array arr;
  arr.add(std::make_unique<Triangle>());
  arr.add(std::make_unique<Hexagon>());

  EXPECT_EQ(arr.size(), 2);
  arr.remove(0);
  EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, RemoveLastFigure) {
  Array arr;
  arr.add(std::make_unique<Triangle>());

  arr.remove(0);
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, RemoveInvalidIndexThrows) {
  Array arr;
  arr.add(std::make_unique<Triangle>());

  EXPECT_THROW(arr.remove(1), std::out_of_range);
  EXPECT_THROW(arr.remove(100), std::out_of_range);
}

TEST(ArrayTest, RemoveFromEmptyArrayThrows) {
  Array arr;
  EXPECT_THROW(arr.remove(0), std::out_of_range);
}

TEST(ArrayTest, GetTotalAreaEmpty) {
  Array arr;
  EXPECT_NEAR(arr.getTotalArea(), 0.0, 1e-9);
}

TEST(ArrayTest, GetTotalAreaSingleFigure) {
  Array arr;
  auto triangle = std::make_unique<Triangle>(Point(0, 0), Point(4, 0), Point(0, 3));
  double expectedArea = triangle->getArea();
  arr.add(std::move(triangle));

  EXPECT_NEAR(arr.getTotalArea(), expectedArea, 1e-9);
}

TEST(ArrayTest, GetTotalAreaMultipleFigures) {
  Array arr;

  auto triangle = std::make_unique<Triangle>(Point(0, 0), Point(4, 0), Point(0, 3));
  double area1 = triangle->getArea();
  arr.add(std::move(triangle));

  auto hexagon = std::make_unique<Hexagon>();
  double area2 = hexagon->getArea();
  arr.add(std::move(hexagon));

  auto octagon = std::make_unique<Octagon>();
  double area3 = octagon->getArea();
  arr.add(std::move(octagon));

  double expectedTotal = area1 + area2 + area3;
  EXPECT_NEAR(arr.getTotalArea(), expectedTotal, 1e-6);
}

TEST(ArrayTest, PrintAllEmpty) {
  Array arr;
  std::ostringstream oss;

  EXPECT_NO_THROW(arr.printAll(oss));
}

TEST(ArrayTest, PrintAllWithFigures) {
  Array arr;
  arr.add(std::make_unique<Triangle>(Point(0, 0), Point(1, 0), Point(0.5, 1)));
  arr.add(std::make_unique<Hexagon>());

  std::ostringstream oss;
  arr.printAll(oss);

  std::string output = oss.str();
  EXPECT_TRUE(output.find("Figure 0") != std::string::npos);
  EXPECT_TRUE(output.find("Figure 1") != std::string::npos);
  EXPECT_TRUE(output.find("Center") != std::string::npos);
  EXPECT_TRUE(output.find("Area") != std::string::npos);
}

TEST(ArrayTest, MoveConstructor) {
  Array arr1;
  arr1.add(std::make_unique<Triangle>());
  arr1.add(std::make_unique<Hexagon>());

  Array arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 2);
}

TEST(ArrayTest, MoveAssignment) {
  Array arr1;
  arr1.add(std::make_unique<Triangle>());
  arr1.add(std::make_unique<Hexagon>());

  Array arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 2);
}

TEST(ArrayTest, PolymorphismTriangle) {
  Array arr;
  arr.add(std::make_unique<Triangle>(Point(0, 0), Point(4, 0), Point(0, 3)));

  Figure* fig = arr.get(0);
  EXPECT_NEAR(fig->getArea(), 6.0, 1e-9);
  EXPECT_NEAR(static_cast<double>(*fig), 6.0, 1e-9);
}

TEST(ArrayTest, PolymorphismMultipleTypes) {
  Array arr;
  arr.add(std::make_unique<Triangle>());
  arr.add(std::make_unique<Hexagon>());
  arr.add(std::make_unique<Octagon>());

  EXPECT_NO_THROW(arr.get(0)->getCenter());
  EXPECT_NO_THROW(arr.get(1)->getCenter());
  EXPECT_NO_THROW(arr.get(2)->getCenter());

  EXPECT_GT(arr.get(0)->getArea(), 0.0);
  EXPECT_GT(arr.get(1)->getArea(), 0.0);
  EXPECT_GT(arr.get(2)->getArea(), 0.0);
}
