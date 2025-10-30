#pragma once

#include "figure.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

namespace geometry {

class Array {
 private:
  std::vector<std::unique_ptr<Figure>> figures_;

 public:
  Array() = default;
  ~Array() = default;

  Array(const Array&) = delete;
  Array& operator=(const Array&) = delete;

  Array(Array&& other) noexcept = default;
  Array& operator=(Array&& other) noexcept = default;

  void add(std::unique_ptr<Figure> figure);

  void remove(size_t index);

  Figure* operator[](size_t index) const;

  size_t size() const {
    return figures_.size();
  }

  double getTotalArea() const;

  void printAll(std::ostream& os) const;
};

}
