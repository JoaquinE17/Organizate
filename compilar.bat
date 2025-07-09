@echo off
::Compilar codigo
g++ main.cpp peaje.cpp vagones.cpp tren.cpp -o Organizate.exe

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
::copy /Y Organizate.exe "%escritorio%\Organizate.exe"
:: [/Y]->Se salta la confirmacion (si el archivo existe)

::Crear acceso directo (Organizate.exe)
powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%escritorio%\Organizate.lnk');$s.TargetPath='%CD%\\Organizate.exe';$s.WorkingDirectory='%CD%';$s.Save()"
::El script de powershell crea o sobrescribe si existe.	Propiedades del acceso directo: {[TargetPath=]->Destino ; [WorkingDirectory=]->Iniciar en}

echo Acceso directo creado en el escritorio

::Ejecutar el programa
::"%escritorio%\Organizate.exe"

pause
