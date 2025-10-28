#include "triangle.hpp"

#include <cmath>

namespace geometry {

Triangle::Triangle() : vertices_{Point(0, 0), Point(1, 0), Point(0.5, std::sqrt(3) / 2)} {}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : vertices_{p1, p2, p3} {}

Triangle::Triangle(const Triangle& other) : vertices_(other.vertices_) {}

Triangle::Triangle(Triangle&& other) noexcept : vertices_(std::move(other.vertices_)) {}

Triangle& Triangle::operator=(const Triangle& other) {
  if (this != &other) {
    vertices_ = other.vertices_;
  }
  return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
  if (this != &other) {
    vertices_ = std::move(other.vertices_);
  }
  return *this;
}

bool Triangle::operator==(const Triangle& other) const {
  for (size_t i = 0; i < VERTICES; ++i) {
    if (!(vertices_[i] == other.vertices_[i])) {
      return false;
    }
  }
  return true;
}

Point Triangle::getCenter() const {
  double centerX = 0.0;
  double centerY = 0.0;
  for (size_t i = 0; i < VERTICES; ++i) {
    centerX += vertices_[i].x;
    centerY += vertices_[i].y;
  }
  return Point(centerX / VERTICES, centerY / VERTICES);
}

double Triangle::getArea() const {
  double area = std::abs((vertices_[0].x * (vertices_[1].y - vertices_[2].y) +
                          vertices_[1].x * (vertices_[2].y - vertices_[0].y) +
                          vertices_[2].x * (vertices_[0].y - vertices_[1].y)) /
                         2.0);
  return area;
}

void Triangle::print(std::ostream& os) const {
  os << "Triangle vertices: ";
  for (size_t i = 0; i < VERTICES; ++i) {
    os << "(" << vertices_[i].x << ", " << vertices_[i].y << ")";
    if (i < VERTICES - 1) {
      os << ", ";
    }
  }
}

void Triangle::read(std::istream& is) {
  for (size_t i = 0; i < VERTICES; ++i) {
    is >> vertices_[i].x >> vertices_[i].y;
  }
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

}  // namespace geometry
