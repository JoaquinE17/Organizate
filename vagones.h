// MENU DE OPCIONES
#ifndef VAGONES_H
#define VAGONES_H

#include "constantes.h"
#include "peaje.h"

typedef char t_flecha[4];
typedef char t_tarea[30];
typedef char t_h2[20];
typedef t_tarea t_matriz[MAX];
typedef t_flecha t_matriz2[MAX];

void crear_lista_nueva(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup);
void previsualizar_lista(t_matriz2 no_hecho, t_matriz tareas, int ocup);
void modificar_lista(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup);
  void modtarea_v(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup); // Vaciar lista
  void modtarea_c(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup); // hacer Cambios en la lista
    void modtarea_tr(t_matriz2 &no_hecho, t_matriz &tareas, int ocup, t_tarea nota_m3); // marcar Tarea Realizada
    void revertir_check(t_matriz2 &no_hecho, t_matriz tareas, int ocup, t_tarea nota_m3);
    void modificar_tarea(t_matriz &tareas, int ocup);
    void modificar_titulo(t_matriz2 &no_hecho, t_matriz &tareas, int ocup);
  void modAgregar_tr(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup); // Agregar Tarea 
void exportar_tarea(t_matriz2 no_hecho, t_matriz tareas, int ocup);


#endif