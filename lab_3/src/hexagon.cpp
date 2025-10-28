#include "hexagon.hpp"

#include <array>
#include <cmath>

namespace geometry {

namespace {
constexpr double PI = 3.14159265358979323846;

std::array<Point, 6> createRegularHexagon() {
  const double RADIUS = 1.0;
  std::array<Point, 6> vertices;
  for (size_t i = 0; i < 6; ++i) {
    double angle = PI / 3.0 * i;
    vertices[i].x = RADIUS * std::cos(angle);
    vertices[i].y = RADIUS * std::sin(angle);
  }
  return vertices;
}
}  // namespace

Hexagon::Hexagon() : vertices_(createRegularHexagon()) {}

Hexagon::Hexagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
                 const Point& p5, const Point& p6)
    : vertices_{p1, p2, p3, p4, p5, p6} {}

Hexagon::Hexagon(const Hexagon& other) : vertices_(other.vertices_) {}

Hexagon::Hexagon(Hexagon&& other) noexcept : vertices_(std::move(other.vertices_)) {}

Hexagon& Hexagon::operator=(const Hexagon& other) {
  if (this != &other) {
    vertices_ = other.vertices_;
  }
  return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
  if (this != &other) {
    vertices_ = std::move(other.vertices_);
  }
  return *this;
}

bool Hexagon::operator==(const Hexagon& other) const {
  for (size_t i = 0; i < VERTICES; ++i) {
    if (!(vertices_[i] == other.vertices_[i])) {
      return false;
    }
  }
  return true;
}

Point Hexagon::getCenter() const {
  double centerX = 0.0;
  double centerY = 0.0;
  for (const auto& vertex : vertices_) {
    centerX += vertex.x;
    centerY += vertex.y;
  }
  return Point(centerX / VERTICES, centerY / VERTICES);
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
  for (size_t i = 0; i < VERTICES; ++i) {
    os << "(" << vertices_[i].x << ", " << vertices_[i].y << ")";
    if (i < VERTICES - 1) {
      os << ", ";
    }
  }
}

void Hexagon::read(std::istream& is) {
  for (auto& vertex : vertices_) {
    is >> vertex.x >> vertex.y;
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

}  // namespace geometry
