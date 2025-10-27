# 🔍 Линтер для лабораторных работ

Этот проект настроен с автоматической проверкой стиля кода для всех лабораторных работ.

## 📁 Структура

```
oop/
├── .clang-format          # Конфигурация форматирования
├── .clang-tidy           # Конфигурация проверки стиля
├── lint_all.bat          # Скрипт проверки (Windows)
├── codestyle.md          # Правила кодстайла
└── lab_2/                # Лабораторные работы
    ├── include/
    ├── src/
    └── tests/
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
clang-format --dry-run --Werror lab_2/src/*.cpp lab_2/include/*.hpp

# Автоматическое форматирование
clang-format -i lab_2/src/*.cpp lab_2/include/*.hpp

# Проверка стиля кода
clang-tidy lab_2/src/*.cpp lab_2/include/*.hpp -- -std=c++17 -Ilab_2/include
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
# Проверка lab_2 (универсально для любой lab_X)
LAB_NAME="lab_2"
clang-format --dry-run --Werror $LAB_NAME/src/*.cpp $LAB_NAME/include/*.hpp
clang-tidy $LAB_NAME/src/*.cpp $LAB_NAME/include/*.hpp -- -std=c++17 -I$LAB_NAME/include
```

Или без переменной:
```bash
# Для lab_2
clang-format --dry-run --Werror lab_2/src/*.cpp lab_2/include/*.hpp
clang-tidy lab_2/src/*.cpp lab_2/include/*.hpp -- -std=c++17 -Ilab_2/include
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
- Проверка использования современных C++ возможностей
- Проверка безопасности памяти

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
clang-format -i lab_2/src/binary.cpp
```

### Проверка конкретного файла:
```bash
clang-tidy lab_2/src/binary.cpp -- -std=c++17 -Ilab_2/include
```

### Автоматическое исправление:
```bash
clang-tidy -fix lab_2/src/binary.cpp -- -std=c++17 -Ilab_2/include
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
