# Organizate

**Organizate** es una aplicación de línea de comandos (CLI) desarrollada con el objetivo de poner en práctica los conocimientos adquiridos en programación. Fue construida utilizando el lenguaje **C++**.

Durante su desarrollo, se aplicaron distintos enfoques para evaluar el comportamiento del programa y resolver los desafíos que surgieron a lo largo del proceso.

## Objetivo

El objetivo principal de *Organizate* es la **organización de tareas pendientes**. La aplicación permite al usuario:

- Marcar tareas como realizadas o en desarrollo
- Desmarcar tareas si se cometió un error
- Guardar el progreso y recuperarlo al reiniciar el programa

Todo esto se implementa mediante el uso de **listas enlazadas**, que representan listas de tareas. A la colección de estas listas la llamamos **itinerario**.

## Funcionalidades

Antes de incorporar una lista de tareas al itinerario, el programa permite:

- Crear listas con **hasta 10 tareas**
- Modificar el **título de la lista**
- Editar cualquier tarea individual
- Marcar o desmarcar tareas realizadas
- Visualizar la lista antes de agregarla al itinerario final

## Compilación

Dado que el proyecto fue dividido en varios archivos y desarrollado en **Windows**, se creó un script en batch (`compilar.bat`) para automatizar su compilación.  
Además, se incluye en el repositorio el ejecutable ya compilado, por si el usuario no cuenta con un compilador.

### Notas

- El compilador utilizado fue **[TDM-GCC]**  
- Los archivos `.h` son archivos de encabezado que contienen constantes y funciones  
- Se realizaron ajustes a la ventana del programa para mejorar la experiencia del usuario  

[TDM-GCC]: https://sourceforge.net/projects/tdm-gcc/
