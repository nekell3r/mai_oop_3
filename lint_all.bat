chcp 65001 >nul
@echo off
echo 🔍 Проверка форматирования и стиля кода для всех лабораторных работ...

for /d %%d in (lab_*) do (
    if exist "%%d" (
        echo 📁 Проверяем %%d...
        
        echo   🎨 Проверка форматирования...
        for /r "%%d" %%f in (*.cpp *.hpp *.h) do (
            clang-format --dry-run --Werror "%%f" >nul 2>&1
            if errorlevel 1 (
                echo     ❌ %%f - нуждается в форматировании
            ) else (
                echo     ✅ %%f - форматирование OK
            )
        )
        
        echo   🔧 Проверка стиля кода...
        for /r "%%d" %%f in (*.cpp *.hpp *.h) do (
            if exist "%%d\include" (
                clang-tidy "%%f" -- -std=c++17 -I%%d\include >nul 2>&1
            ) else (
                clang-tidy "%%f" -- -std=c++17 >nul 2>&1
            )
            if errorlevel 1 (
                echo     ⚠️  %%f - есть предупреждения стиля
            ) else (
                echo     ✅ %%f - стиль OK
            )
        )
        
        echo   ✅ %%d проверен
        echo.
    )
)

echo 🎉 Проверка завершена!
pause
