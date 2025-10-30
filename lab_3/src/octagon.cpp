#include "octagon.hpp"

#include <array>
#include <cmath>

namespace geometry {

namespace {
constexpr double PI = 3.14159265358979323846;

std::array<Point, 8> createRegularOctagon() {
  std::array<Point, 8> vertices;
  for (size_t i = 0; i < 8; i++) {
    double angle = (PI / 4.0) * i;
    vertices[i] = Point(std::cos(angle), std::sin(angle));
  }
  return vertices;
}
}

Octagon::Octagon() : vertices_(createRegularOctagon()) {}

Octagon::Octagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
                 const Point& p5, const Point& p6, const Point& p7, const Point& p8)
    : vertices_{p1, p2, p3, p4, p5, p6, p7, p8} {}

bool Octagon::operator==(const Octagon& other) const {
  for (size_t i = 0; i < VERTICES; ++i) {
    if (!(vertices_[i] == other.vertices_[i])) {
      return false;
    }
  }
  return true;
}

Point Octagon::getCenter() const {
  Point center;
  for (const auto& v : vertices_) {
    center.x += v.x;
    center.y += v.y;
  }
  center.x /= 8;
  center.y /= 8;
  return center;
}

double Octagon::getArea() const {
  double area = 0.0;
  for (size_t i = 0; i < VERTICES; ++i) {
    size_t j = (i + 1) % VERTICES;
    area += vertices_[i].x * vertices_[j].y;
    area -= vertices_[j].x * vertices_[i].y;
  }
  return std::abs(area) / 2.0;
}

void Octagon::print(std::ostream& os) const {
  os << "Octagon vertices: ";
  bool first = true;
  for (const auto& v : vertices_) {
    if (!first) os << ", ";
    os << "(" << v.x << ", " << v.y << ")";
    first = false;
  }
}

void Octagon::read(std::istream& is) {
  for (size_t i = 0; i < vertices_.size(); i++) {
    is >> vertices_[i];
  }
}

std::unique_ptr<Figure> Octagon::clone() const {
  return std::make_unique<Octagon>(*this);
}

bool Octagon::isEqual(const Figure& other) const {
  const auto* otherOctagon = dynamic_cast<const Octagon*>(&other);
  if (otherOctagon == nullptr) {
    return false;
  }
  return *this == *otherOctagon;
}

}
