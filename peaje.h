// CONTROL - FLUJO DE ACCIONES
#ifndef PEAJE_H
#define PEAJE_H

#include "constantes.h"
#include "vagones.h"

typedef char t_tarea[30];
typedef t_tarea t_matriz[MAX];

void cancelar_ingreso(t_matriz tareas, int &ocup);
void continuar();

// ESCAPE-CODE (enable)
void HabilitarAnsiEscapeCodes();

// Manipular ventana
void desactivarMaximizar();

// Menus
void menu_main();
void menu_vagones();
void menu_vagones_cambios();
void menu_tren();

#endif