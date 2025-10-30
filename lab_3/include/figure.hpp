#pragma once

#include <iostream>
#include <memory>

namespace geometry {

struct Point {
  double x, y;

  Point() : x(0), y(0) {}
  Point(double xVal, double yVal) : x(xVal), y(yVal) {}

  bool operator==(const Point& other) const {
    static constexpr double EPS = 1e-9;
    double dx = x - other.x;
    double dy = y - other.y;
    return (dx * dx + dy * dy) < EPS * EPS;
  }

  friend std::ostream& operator<<(std::ostream& os, const Point& p);
  friend std::istream& operator>>(std::istream& is, Point& p);
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

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << p.x << " " << p.y;
  return os;
}

inline std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

}
