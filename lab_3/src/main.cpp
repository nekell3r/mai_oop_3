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
  std::cout << "\n1. Треугольник\n";
  std::cout << "2. Шестиугольник\n";
  std::cout << "3. Восьмиугольник\n";
  std::cout << "4. Показать\n";
  std::cout << "5. Площадь\n";
  std::cout << "6. Удалить\n";
  std::cout << "0. Выход\n";
  std::cout << "> ";
}

void addTriangle(Array& arr) {
  std::cout << "3 вершины (x y): ";
  auto triangle = std::make_unique<Triangle>();
  std::cin >> *triangle;
  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка!\n";
    return;
  }
  arr.add(std::move(triangle));
  std::cout << "ОК\n";
}

void addHexagon(Array& arr) {
  std::cout << "6 вершин (x y): ";
  std::unique_ptr<Hexagon> hexagon = std::make_unique<Hexagon>();
  std::cin >> *hexagon;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка!\n";
    return;
  }
  arr.add(std::move(hexagon));
  std::cout << "ОК\n";
}

void addOctagon(Array& arr) {
  std::cout << "8 вершин (x y): ";
  auto octagon = std::make_unique<Octagon>();
  std::cin >> *octagon;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка!\n";
    return;
  }
  arr.add(std::move(octagon));
  std::cout << "ОК\n";
}

void showAllFigures(const Array& arr) {
  if (!arr.size()) {
    std::cout << "Пусто\n";
    return;
  }
  arr.printAll(std::cout);
}

void showTotalArea(const Array& arr) {
  std::cout << "Площадь: " << arr.getTotalArea() << "\n";
}

void removeFigure(Array& arr) {
  if (arr.size() == 0) {
    std::cout << "Пусто\n";
    return;
  }
  std::cout << "Индекс (0-" << (arr.size() - 1) << "): ";
  int index;
  std::cin >> index;
  if (std::cin.fail() || index < 0) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Ошибка!\n";
    return;
  }
  try {
    arr.remove(static_cast<size_t>(index));
    std::cout << "Удалено\n";
  } catch (const std::exception& e) {
    std::cout << "Ошибка: " << e.what() << "\n";
  }
}

}

int main() {
  Array arr;
  int choice;
  while (true) {
    printMenu();
    std::cin >> choice;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Ошибка!\n";
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
      std::cout << "?\n";
    }
  }
  
  return 0;
}
