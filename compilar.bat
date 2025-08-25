@echo off
::COMPILAR CODIGO

:: Linea nesesaria para incrustar el 'icono.ico' en el programa principal (main)
:: [windres] es una herramienta del compilador (MinGW), convierte '.rc' a '.o' (objeto compatible)
windres recursos.rc -o recursos.o

::g++ main.cpp peaje.cpp vagones.cpp tren.cpp -o Organizate.exe
:: Genera un ejecutable sin enlace estático.


g++ main.cpp peaje.cpp vagones.cpp tren.cpp recursos.o -static -o Organizate.exe 
:: Le dice al compilador que genere un ejecutable con enlace estático.
:: [static] -> En lugar de depender de bibliotecas externas esté incluye todas las necesarias dentro del ejecutable

::VERIFICAR ERROR
if %errorlevel% neq 0 (
	echo Error al compilar.
	pause
	exit /b
)

echo Compilacion exitosa.

::ASIGNAR RUTA DE DIRECTORIO
set escritorio=%USERPROFILE%\Desktop

::COPIAR EJECUTABLE AL ESCRITORIO
::copy /Y Organizate.exe "%escritorio%\Organizate.exe"
:: [/Y]->Se salta la confirmacion (si el archivo existe)

::CREAR ACCESO DIRECTO (Organizate.exe)
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%escritorio%\Organizate.lnk');$s.TargetPath='%CD%\\Organizate.exe';$s.WorkingDirectory='%CD%';$s.Save()"
:: El script de powershell crea o sobrescribe si existe.	
:: Propiedades del acceso directo: {[TargetPath=]->Destino ; [WorkingDirectory=]->Iniciar en}

echo Acceso directo creado en el escritorio

::EJECUTAR EL EJECUTABLE
::"%escritorio%\Organizate.exe"

pause
