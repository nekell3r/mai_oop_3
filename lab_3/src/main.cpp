#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

#include <iostream>
#include <sstream>

using namespace geometry;

namespace {

void printMenu() {
  std::cout << "\n=== Меню ===" << std::endl;
  std::cout << "1. Добавить треугольник" << std::endl;
  std::cout << "2. Добавить шестиугольник" << std::endl;
  std::cout << "3. Добавить восьмиугольник" << std::endl;
  std::cout << "4. Показать все фигуры" << std::endl;
  std::cout << "5. Вычислить общую площадь" << std::endl;
  std::cout << "6. Удалить фигуру по индексу" << std::endl;
  std::cout << "0. Выход" << std::endl;
  std::cout << "Выберите действие: ";
}

void addTriangle(Array& arr) {
  std::cout << "Введите координаты 3 вершин треугольника (x1 y1 x2 y2 x3 y3): " << std::endl;
  auto triangle = std::make_unique<Triangle>();
  std::cin >> *triangle;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка ввода!" << std::endl;
    return;
  }
  arr.add(std::move(triangle));
  std::cout << "Треугольник добавлен!" << std::endl;
}

void addHexagon(Array& arr) {
  std::cout << "Введите координаты 6 вершин шестиугольника (x1 y1 x2 y2 ... x6 y6): " << std::endl;
  auto hexagon = std::make_unique<Hexagon>();
  std::cin >> *hexagon;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка ввода!" << std::endl;
    return;
  }
  arr.add(std::move(hexagon));
  std::cout << "Шестиугольник добавлен!" << std::endl;
}

void addOctagon(Array& arr) {
  std::cout << "Введите координаты 8 вершин восьмиугольника (x1 y1 x2 y2 ... x8 y8): " << std::endl;
  auto octagon = std::make_unique<Octagon>();
  std::cin >> *octagon;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка ввода!" << std::endl;
    return;
  }
  arr.add(std::move(octagon));
  std::cout << "Восьмиугольник добавлен!" << std::endl;
}

void showAllFigures(const Array& arr) {
  if (arr.size() == 0) {
    std::cout << "Массив пуст!" << std::endl;
    return;
  }
  std::cout << "\n=== Все фигуры ===" << std::endl;
  arr.printAll(std::cout);
}

void showTotalArea(const Array& arr) {
  std::cout << "Общая площадь всех фигур: " << arr.getTotalArea() << std::endl;
}

void removeFigure(Array& arr) {
  if (arr.size() == 0) {
    std::cout << "Массив пуст!" << std::endl;
    return;
  }
  std::cout << "Введите индекс фигуры для удаления (0-" << (arr.size() - 1) << "): ";
  size_t index;
  std::cin >> index;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка ввода!" << std::endl;
    return;
  }
  try {
    arr.remove(index);
    std::cout << "Фигура удалена!" << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Ошибка: " << e.what() << std::endl;
  }
}

}  // namespace

int main() {
  Array arr;

  std::cout << "=== Лабораторная работа №3: Фигуры вращения ===" << std::endl;
  std::cout << "Вариант 23: Треугольник, Шестиугольник, Восьмиугольник" << std::endl;

  int choice = -1;
  while (choice != 0) {
    printMenu();
    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Неверный ввод!" << std::endl;
      continue;
    }

    switch (choice) {
    case 1:
      addTriangle(arr);
      break;
    case 2:
      addHexagon(arr);
      break;
    case 3:
      addOctagon(arr);
      break;
    case 4:
      showAllFigures(arr);
      break;
    case 5:
      showTotalArea(arr);
      break;
    case 6:
      removeFigure(arr);
      break;
    case 0:
      std::cout << "До свидания!" << std::endl;
      break;
    default:
      std::cout << "Неверный выбор!" << std::endl;
    }
  }

  return 0;
}
