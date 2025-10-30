#include "array.hpp"

namespace geometry {

void Array::add(std::unique_ptr<Figure> figure) {
  if (figure == nullptr) {
    throw std::invalid_argument("Cannot add null figure to array");
  }
  figures_.push_back(std::move(figure));
}

void Array::remove(size_t index) {
  if (index >= figures_.size()) {
    throw std::out_of_range("Index out of range");
  }
  figures_.erase(figures_.begin() + static_cast<long>(index));
}

Figure* Array::get(size_t index) const {
  if (index >= figures_.size()) {
    throw std::out_of_range("Index out of range");
  }
  return figures_[index].get();
}

double Array::getTotalArea() const {
  double total = 0;
  for (size_t i = 0; i < figures_.size(); i++) {
    total += figures_[i]->getArea();
  }
  return total;
}

void Array::printAll(std::ostream& os) const {
  for (size_t i = 0; i < figures_.size(); i++) {
    os << "Figure " << i << ":\n";
    os << "  " << *figures_[i] << "\n";
    Point center = figures_[i]->getCenter();
    os << "  Center: (" << center.x << ", " << center.y << ")\n";
    os << "  Area: " << figures_[i]->getArea() << "\n";
  }
}

}
