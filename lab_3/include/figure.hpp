#pragma once

#include <iostream>
#include <memory>

namespace geometry {

constexpr double EPS = 1e-9;

struct Point {
  double x, y;

  Point() : x(0), y(0) {}
  Point(double xVal, double yVal) : x(xVal), y(yVal) {}

  bool operator==(const Point& other) const {
    return (std::abs(x - other.x) < EPS) && (std::abs(y - other.y) < EPS);
  }
};

class Figure {
 public:
  virtual ~Figure() = default;

  virtual Point getCenter() const = 0;

  virtual double getArea() const = 0;

  explicit operator double() const {
    return getArea();
  }

  virtual void print(std::ostream& os) const = 0;

  virtual void read(std::istream& is) = 0;

  virtual std::unique_ptr<Figure> clone() const = 0;

  virtual bool isEqual(const Figure& other) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Figure& figure) {
  figure.print(os);
  return os;
}

inline std::istream& operator>>(std::istream& is, Figure& figure) {
  figure.read(is);
  return is;
}

}
