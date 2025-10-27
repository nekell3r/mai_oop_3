chcp 65001 >nul
@echo off
setlocal enabledelayedexpansion

echo 🔍 Проверка форматирования и стиля кода для всех лабораторных работ...
echo.

set ERROR_COUNT=0
set FILE_COUNT=0

for /d %%d in (lab_*) do (
    if exist "%%d" (
        echo 📁 Проверяем %%d...
        
        REM Проверка форматирования
        echo   🎨 Проверка форматирования...
        for %%s in (src include tests) do (
            if exist "%%d\%%s" (
                for /r "%%d\%%s" %%f in (*.cpp *.hpp *.h) do (
                    set /a FILE_COUNT+=1
                    clang-format --dry-run --Werror "%%f" >nul 2>&1
                    if errorlevel 1 (
                        echo     ❌ %%f - нуждается в форматировании
                        set /a ERROR_COUNT+=1
                    ) else (
                        echo     ✅ %%f - форматирование OK
                    )
                )
            )
        )
        
        REM Проверка стиля кода
        echo   🔧 Проверка стиля кода...
        for %%s in (src include tests) do (
            if exist "%%d\%%s" (
                for /r "%%d\%%s" %%f in (*.cpp *.hpp *.h) do (
                    if exist "%%d\include" (
                        clang-tidy "%%f" -p=%%d -- -std=c++17 -I%%d\include >nul 2>&1
                    ) else (
                        clang-tidy "%%f" -- -std=c++17 >nul 2>&1
                    )
                    if errorlevel 1 (
                        echo     ⚠️  %%f - есть предупреждения стиля
                    ) else (
                        echo     ✅ %%f - стиль OK
                    )
                )
            )
        )
        
        echo   ✅ %%d проверен
        echo.
    )
)

echo.
echo 📊 Статистика:
echo   Проверено файлов: !FILE_COUNT!
echo   Ошибок форматирования: !ERROR_COUNT!
echo.
if !ERROR_COUNT! equ 0 (
    echo 🎉 Все проверки пройдены успешно!
) else (
    echo ⚠️  Обнаружены ошибки. Запустите форматирование: clang-format -i lab_*/src/*.cpp lab_*/include/*.hpp
)
echo.
pause
