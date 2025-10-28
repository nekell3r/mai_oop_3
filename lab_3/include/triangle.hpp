#pragma once

#include "figure.hpp"

#include <array>
#include <cmath>

namespace geometry {

class Triangle : public Figure {
 private:
  static constexpr size_t VERTICES = 3;
  std::array<Point, VERTICES> vertices_;

 public:
  Triangle();
  Triangle(const Point& p1, const Point& p2, const Point& p3);
  Triangle(const Triangle& other);
  Triangle(Triangle&& other) noexcept;

  Triangle& operator=(const Triangle& other);
  Triangle& operator=(Triangle&& other) noexcept;
  bool operator==(const Triangle& other) const;

  Point getCenter() const override;
  double getArea() const override;
  void print(std::ostream& os) const override;
  void read(std::istream& is) override;
  std::unique_ptr<Figure> clone() const override;
  bool isEqual(const Figure& other) const override;

  const std::array<Point, VERTICES>& getVertices() const {
    return vertices_;
  }
};

}  // namespace geometry
