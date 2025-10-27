# 🔍 Линтер для лабораторных работ

Этот проект настроен с автоматической проверкой стиля кода для всех лабораторных работ.

## 📁 Структура

```
mai_oop_3/
├── .clang-format          # Конфигурация форматирования
├── .clang-tidy           # Конфигурация проверки стиля
├── .cursorignore         # Исключения для IDE
├── .gitignore            # Исключения для Git
├── lint_all.bat          # Скрипт проверки (Windows)
├── codestyle.md          # Правила кодстайла
├── LINTING.md            # Документация по линтингу
└── lab_3/                # Лабораторная работа №3
    ├── CMakeLists.txt    # Конфигурация CMake
    ├── include/          # Заголовочные файлы (.h, .hpp)
    ├── src/              # Исходные файлы (.cpp)
    └── tests/            # Google Test тесты
```

## 🚀 Использование

### Автоматическая проверка всех лаб

**Linux/Mac:**
```bash
./lint_all.sh
```

**Windows:**
```cmd
lint_all.bat
```

### Ручная проверка

**Windows** (используйте команды напрямую или `lint_all.bat`):
```powershell
# Проверка форматирования
clang-format --dry-run --Werror lab_3/src/*.cpp lab_3/include/*.hpp

# Автоматическое форматирование
clang-format -i lab_3/src/*.cpp lab_3/include/*.hpp

# Проверка стиля кода
clang-tidy lab_3/src/*.cpp lab_3/include/*.hpp -- -std=c++17 -Ilab_3/include
```

**Linux/Mac** (с Makefile):
```bash
make lint          # проверить форматирование
make format        # автоматически отформатировать код
make check-style   # проверить стиль кода
make check-all     # выполнить все проверки
```

> **Примечание**: 
> - Чтобы использовать `make` в Windows с MSYS2, добавьте `C:\msys64\usr\bin` в PATH или используйте полный путь: `C:\msys64\usr\bin\make.exe`
> - Альтернативно установите WSL (Windows Subsystem for Linux)
> - В PowerShell `make` требует правильной настройки путей MSYS2 в PATH

### Проверка конкретной лабы

```bash
# Проверка lab_3 (универсально для любой lab_X)
LAB_NAME="lab_3"
clang-format --dry-run --Werror $LAB_NAME/src/*.cpp $LAB_NAME/include/*.hpp
clang-tidy $LAB_NAME/src/*.cpp $LAB_NAME/include/*.hpp -- -std=c++17 -I$LAB_NAME/include
```

Или без переменной:
```bash
# Для lab_3
clang-format --dry-run --Werror lab_3/src/*.cpp lab_3/include/*.hpp
clang-tidy lab_3/src/*.cpp lab_3/include/*.hpp -- -std=c++17 -Ilab_3/include
```

## ⚙️ Настройки

### Форматирование (.clang-format)
- Основан на Google Style Guide
- Отступы: 2 пробела
- Максимальная длина строки: 100 символов
- Автоматическая сортировка include'ов

### Проверка стиля (.clang-tidy)
- Проверка именования: CamelCase для классов, camelBack для функций
- Проверка const-correctness
- Проверка использования современных C++ возможностей (modernize-*)
- Проверка безопасности памяти и багов (bugprone-*, cert-*)
- Проверка производительности (performance-*)
- Статический анализ кода (clang-analyzer-*)
- Проверка читаемости (readability-*)
- Рекомендации C++ Core Guidelines (cppcoreguidelines-*)

## 🔧 Установка инструментов

### Ubuntu/Debian:
```bash
sudo apt-get install clang-format clang-tidy
```

### Windows (MSYS2):
```bash
pacman -S mingw-w64-x86_64-clang-tools-extra
```

### macOS:
```bash
brew install clang-format clang-tidy
```

## 📝 Примеры использования

### Форматирование файла:
```bash
clang-format -i lab_3/src/figure.cpp
```

### Проверка конкретного файла:
```bash
clang-tidy lab_3/src/figure.cpp -- -std=c++17 -Ilab_3/include
```

### Автоматическое исправление:
```bash
clang-tidy -fix lab_3/src/figure.cpp -- -std=c++17 -Ilab_3/include
```

## 🎯 Рекомендации

1. **Перед коммитом** всегда запускайте `make check-all`
2. **Используйте IDE интеграцию** для автоматического форматирования
3. **Настройте pre-commit hooks** для автоматической проверки
4. **Изучайте предупреждения** clang-tidy для улучшения кода

## 🐛 Устранение проблем

### Ошибка "command not found":
Убедитесь, что clang-format и clang-tidy установлены и доступны в PATH.

### Много предупреждений:
Начните с исправления критических ошибок, затем переходите к предупреждениям.

### Конфликты форматирования:
Используйте `clang-format -i` для автоматического исправления.
