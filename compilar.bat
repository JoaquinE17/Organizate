@echo off
::Compilar codigo
g++ main.cpp peaje.cpp vagones.cpp -o Organizate.exe

::Verificar error
if %errorlevel% neq 0 (
	echo Error al compilar.
	pause
	exit /b
)

echo Compilacion exitosa.

::Asignar ruta de escritorio
set escritorio=%USERPROFILE%\Desktop

::Copiar el ejecutable al escritorio
copy /Y Organizate.exe "%escritorio%\Organizate.exe"

echo Ejecutable copiado al escritorio

::Ejecutar el programa
::"%escritorio%\Organizate.exe"

pause
