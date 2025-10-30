#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "triangle.hpp"

#include <iostream>
#include <sstream>

namespace {

using geometry::Array;
using geometry::Triangle;
using geometry::Hexagon;
using geometry::Octagon;

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
  if (!std::cin) {
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
  std::unique_ptr<Hexagon> hexagon = std::make_unique<Hexagon>();
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
  if (!arr.size()) {
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
  int index;
  std::cin >> index;
  if (std::cin.fail() || index < 0) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка ввода!" << std::endl;
    return;
  }
  try {
    arr.remove(static_cast<size_t>(index));
    std::cout << "Фигура удалена!" << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Ошибка: " << e.what() << std::endl;
  }
}

}

int main() {
  Array arr;

  std::cout << "=== Лабораторная работа №3: Фигуры вращения ===" << std::endl;
  std::cout << "Вариант 23: Треугольник, Шестиугольник, Восьмиугольник" << std::endl;

  int choice;
  while (true) {
    printMenu();
    std::cin >> choice;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Неверный ввод!" << std::endl;
      continue;
    }
    
    if (choice == 0) break;

    if (choice == 1) {
      addTriangle(arr);
    } else if (choice == 2) {
      addHexagon(arr);
    } else if (choice == 3) {
      addOctagon(arr);
    } else if (choice == 4) {
      showAllFigures(arr);
    } else if (choice == 5) {
      showTotalArea(arr);
    } else if (choice == 6) {
      removeFigure(arr);
    } else {
      std::cout << "Неверный выбор!" << std::endl;
    }
  }
  
  std::cout << "До свидания!" << std::endl;
  return 0;
}
