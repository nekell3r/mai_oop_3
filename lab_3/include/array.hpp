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

  // Запрещаем копирование (т.к. используем unique_ptr)
  Array(const Array&) = delete;
  Array& operator=(const Array&) = delete;

  // Разрешаем перемещение
  Array(Array&& other) noexcept = default;
  Array& operator=(Array&& other) noexcept = default;

  // Добавление фигуры в массив
  void add(std::unique_ptr<Figure> figure);

  // Удаление фигуры по индексу
  void remove(size_t index);

  // Получение фигуры по индексу
  Figure* get(size_t index) const;

  // Получение количества фигур
  size_t size() const {
    return figures_.size();
  }

  // Вычисление общей площади всех фигур
  double getTotalArea() const;

  // Печать всех фигур с их центрами и площадями
  void printAll(std::ostream& os) const;
};

}  // namespace geometry
