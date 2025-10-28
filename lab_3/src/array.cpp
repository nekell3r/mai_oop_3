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
  figures_.erase(figures_.begin() + index);
}

Figure* Array::get(size_t index) const {
  if (index >= figures_.size()) {
    throw std::out_of_range("Index out of range");
  }
  return figures_[index].get();
}

double Array::getTotalArea() const {
  double totalArea = 0.0;
  for (const auto& figure : figures_) {
    totalArea += figure->getArea();
  }
  return totalArea;
}

void Array::printAll(std::ostream& os) const {
  for (size_t i = 0; i < figures_.size(); ++i) {
    const auto& figure = figures_[i];
    os << "Figure " << i << ":\n";
    os << "  " << *figure << "\n";
    const auto center = figure->getCenter();
    os << "  Center: (" << center.x << ", " << center.y << ")\n";
    os << "  Area: " << figure->getArea() << "\n";
  }
}

}  // namespace geometry
