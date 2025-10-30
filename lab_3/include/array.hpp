#pragma once

#include "figure.hpp"

#include <memory>
#include <stdexcept>

namespace geometry {

class Array {
 private:
  Figure** data_;
  size_t size_;
  size_t capacity_;

  void resize();

 public:
  Array();
  ~Array();

  Array(const Array&) = delete;
  Array& operator=(const Array&) = delete;

  Array(Array&& other) noexcept;
  Array& operator=(Array&& other) noexcept;

  void add(std::unique_ptr<Figure> figure);

  void remove(size_t index);

  Figure* operator[](size_t index) const;

  size_t size() const {
    return size_;
  }

  double getTotalArea() const;

  void printAll(std::ostream& os) const;
};

}
