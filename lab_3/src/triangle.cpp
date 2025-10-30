#include "triangle.hpp"

#include <cmath>

namespace geometry {

Triangle::Triangle() : vertices_{Point(0, 0), Point(1, 0), Point(0.5, std::sqrt(3) / 2)} {}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : vertices_{p1, p2, p3} {}

bool Triangle::operator==(const Triangle& other) const {
  return (vertices_[0] == other.vertices_[0]) &&
         (vertices_[1] == other.vertices_[1]) &&
         (vertices_[2] == other.vertices_[2]);
}

Point Triangle::getCenter() const {
  return Point((vertices_[0].x + vertices_[1].x + vertices_[2].x) / 3.0,
               (vertices_[0].y + vertices_[1].y + vertices_[2].y) / 3.0);
}

double Triangle::getArea() const {
  double area = std::abs((vertices_[0].x * (vertices_[1].y - vertices_[2].y) +
                          vertices_[1].x * (vertices_[2].y - vertices_[0].y) +
                          vertices_[2].x * (vertices_[0].y - vertices_[1].y)) /
                         2.0);
  return area;
}

void Triangle::print(std::ostream& os) const {
  os << "Triangle vertices: (" << vertices_[0].x << ", " << vertices_[0].y << "), "
     << "(" << vertices_[1].x << ", " << vertices_[1].y << "), "
     << "(" << vertices_[2].x << ", " << vertices_[2].y << ")";
}

void Triangle::read(std::istream& is) {
  is >> vertices_[0].x >> vertices_[0].y;
  is >> vertices_[1].x >> vertices_[1].y;
  is >> vertices_[2].x >> vertices_[2].y;
}

std::unique_ptr<Figure> Triangle::clone() const {
  return std::make_unique<Triangle>(*this);
}

bool Triangle::isEqual(const Figure& other) const {
  const auto* otherTriangle = dynamic_cast<const Triangle*>(&other);
  if (otherTriangle == nullptr) {
    return false;
  }
  return *this == *otherTriangle;
}

}
