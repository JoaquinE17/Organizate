// CONTROL - FLUJO DE ACCIONES
#ifndef PEAJE_H
#define PEAJE_H

#include "constantes.h"

typedef char t_tarea[30];
typedef t_tarea t_matriz[MAX];

void cancelar_ingreso(t_matriz tareas, int &ocup);
void continuar();

// ESCAPE-CODE (enable)
void HabilitarAnsiEscapeCodes();

#endif