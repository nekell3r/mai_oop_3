#pragma once

#include "figure.hpp"

#include <array>
#include <cmath>

namespace geometry {

class Octagon : public Figure {
 private:
  static constexpr size_t VERTICES = 8;
  std::array<Point, VERTICES> vertices_;

 public:
  Octagon();
  Octagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5,
          const Point& p6, const Point& p7, const Point& p8);
  Octagon(const Octagon& other);
  Octagon(Octagon&& other) noexcept;

  Octagon& operator=(const Octagon& other);
  Octagon& operator=(Octagon&& other) noexcept;
  bool operator==(const Octagon& other) const;

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
