#include "array.hpp"

namespace geometry {

Array::Array() : data_(nullptr), size_(0), capacity_(0) {}

Array::~Array() {
  for (size_t i = 0; i < size_; ++i) {
    delete data_[i];
  }
  delete[] data_;
}

Array::Array(Array&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Array& Array::operator=(Array&& other) noexcept {
  if (this != &other) {
    for (size_t i = 0; i < size_; ++i) {
      delete data_[i];
    }
    delete[] data_;
    
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

void Array::resize() {
  size_t newCapacity = (capacity_ == 0) ? 4 : capacity_ * 2;
  Figure** newData = new Figure*[newCapacity];
  
  for (size_t i = 0; i < size_; ++i) {
    newData[i] = data_[i];
  }
  
  delete[] data_;
  data_ = newData;
  capacity_ = newCapacity;
}

void Array::add(std::unique_ptr<Figure> figure) {
  if (figure == nullptr) {
    throw std::invalid_argument("Cannot add null figure to array");
  }
  
  if (size_ >= capacity_) {
    resize();
  }
  
  data_[size_++] = figure.release();
}

void Array::remove(size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  
  delete data_[index];
  
  for (size_t i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  
  --size_;
}

Figure* Array::operator[](size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

double Array::getTotalArea() const {
  double total = 0;
  for (size_t i = 0; i < size_; i++) {
    total += data_[i]->getArea();
  }
  return total;
}

void Array::printAll(std::ostream& os) const {
  for (size_t i = 0; i < size_; i++) {
    os << "Figure " << i << ":\n";
    os << "  " << *data_[i] << "\n";
    Point center = data_[i]->getCenter();
    os << "  Center: (" << center.x << ", " << center.y << ")\n";
    os << "  Area: " << data_[i]->getArea() << "\n";
  }
}

}
