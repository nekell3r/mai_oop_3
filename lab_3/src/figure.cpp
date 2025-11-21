#include "figure.hpp"

namespace geometry {

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
  figure.print(os);
  return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
  figure.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << p.x << " " << p.y;
  return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

}

