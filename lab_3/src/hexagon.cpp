#include "hexagon.hpp"

#include <array>
#include <cmath>

namespace geometry {

namespace {
constexpr double PI = 3.14159265358979323846;

std::array<Point, 6> createRegularHexagon() {
  std::array<Point, 6> vertices;
  double radius = 1.0;
  for (int i = 0; i < 6; i++) {
    double angle = PI / 3.0 * i;
    vertices[i].x = radius * std::cos(angle);
    vertices[i].y = radius * std::sin(angle);
  }
  return vertices;
}
}

Hexagon::Hexagon() : vertices_(createRegularHexagon()) {}

Hexagon::Hexagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
                 const Point& p5, const Point& p6)
    : vertices_{p1, p2, p3, p4, p5, p6} {}

bool Hexagon::operator==(const Hexagon& other) const {
  for (size_t i = 0; i < VERTICES; ++i) {
    if (!(vertices_[i] == other.vertices_[i])) {
      return false;
    }
  }
  return true;
}

Point Hexagon::getCenter() const {
  double sumX = 0, sumY = 0;
  for (size_t i = 0; i < VERTICES; i++) {
    sumX += vertices_[i].x;
    sumY += vertices_[i].y;
  }
  return Point(sumX / 6, sumY / 6);
}

double Hexagon::getArea() const {
  double area = 0.0;
  for (size_t i = 0; i < VERTICES; ++i) {
    size_t j = (i + 1) % VERTICES;
    area += vertices_[i].x * vertices_[j].y;
    area -= vertices_[j].x * vertices_[i].y;
  }
  return std::abs(area) / 2.0;
}

void Hexagon::print(std::ostream& os) const {
  os << "Hexagon vertices: ";
  for (size_t i = 0; i < 6; ++i) {
    if (i > 0) os << ", ";
    os << "(" << vertices_[i].x << ", " << vertices_[i].y << ")";
  }
}

void Hexagon::read(std::istream& is) {
  for (int i = 0; i < 6; i++) {
    is >> vertices_[i];
  }
}

std::unique_ptr<Figure> Hexagon::clone() const {
  return std::make_unique<Hexagon>(*this);
}

bool Hexagon::isEqual(const Figure& other) const {
  const auto* otherHexagon = dynamic_cast<const Hexagon*>(&other);
  if (otherHexagon == nullptr) {
    return false;
  }
  return *this == *otherHexagon;
}

}
