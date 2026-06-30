@echo off
echo ========================================
echo Compilando EDD CoffeeTrack Fase 2...
echo ========================================

REM crea carpetas necesarias si no existen
if not exist certificados (
    mkdir certificados
    echo Carpeta 'certificados' creada.
)
if not exist reportes (
    mkdir reportes
    echo Carpeta 'reportes' creada.
)
if not exist data (
    mkdir data
    echo Carpeta 'data' creada.
)

REM compila todos los archivos .cpp en la carpeta src usando g++
g++ src\*.cpp -o CoffeeTrack.exe

REM 3. Verificar si la compilacion fue exitosa
if %ERRORLEVEL% EQU 0 (
    echo.
    echo [EXITO] Compilacion terminada sin errores.
    echo Iniciando el sistema...
    echo ========================================
    echo.
    CoffeeTrack.exe
) else (
    echo.
    echo [ERROR] Hubo problemas durante la compilacion. Revisa la consola arriba.
)

pause