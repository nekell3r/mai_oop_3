#pragma once

#include <iostream>
#include <memory>

namespace geometry {

// Константа для сравнения вещественных чисел
constexpr double EPS = 1e-9;

// Структура для представления точки в 2D пространстве
struct Point {
  double x;
  double y;

  Point() : x(0.0), y(0.0) {}
  Point(double xVal, double yVal) : x(xVal), y(yVal) {}

  bool operator==(const Point& other) const {
    return (std::abs(x - other.x) < EPS) && (std::abs(y - other.y) < EPS);
  }
};

// Базовый абстрактный класс для всех фигур
class Figure {
 public:
  virtual ~Figure() = default;

  // Вычисление геометрического центра фигуры
  virtual Point getCenter() const = 0;

  // Вычисление площади фигуры
  virtual double getArea() const = 0;

  // Перегрузка оператора приведения к double для получения площади
  explicit operator double() const {
    return getArea();
  }

  // Вывод координат вершин в поток
  virtual void print(std::ostream& os) const = 0;

  // Чтение координат вершин из потока
  virtual void read(std::istream& is) = 0;

  // Клонирование фигуры (для копирования полиморфных объектов)
  virtual std::unique_ptr<Figure> clone() const = 0;

  // Сравнение фигур
  virtual bool isEqual(const Figure& other) const = 0;
};

// Перегрузка оператора << для вывода
inline std::ostream& operator<<(std::ostream& os, const Figure& figure) {
  figure.print(os);
  return os;
}

// Перегрузка оператора >> для ввода
inline std::istream& operator>>(std::istream& is, Figure& figure) {
  figure.read(is);
  return is;
}

}  // namespace geometry
