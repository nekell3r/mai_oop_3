#pragma once

#include "figure.hpp"

#include <array>
#include <cmath>

namespace geometry {

class Hexagon : public Figure {
 private:
  static constexpr size_t VERTICES = 6;
  std::array<Point, VERTICES> vertices_;

 public:
  Hexagon();
  Hexagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5,
          const Point& p6);
  Hexagon(const Hexagon& other);
  Hexagon(Hexagon&& other) noexcept;

  Hexagon& operator=(const Hexagon& other);
  Hexagon& operator=(Hexagon&& other) noexcept;
  bool operator==(const Hexagon& other) const;

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
