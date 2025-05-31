// ALMACENAMIENTO DE TAREAS - LISTAS_ENLASADAS
#ifndef TREN_H
#define TREN_H

#include "constantes.h"
#include "peaje.h"
#include "vagones.h"

typedef t_tarea t_matriz[MAX];
typedef char t_h2[20];
struct nodo{ 
	t_matriz vagon;
	int cantidad;
	nodo* siguiente; // Permite enlasar nodos
};

void construir_lista_tareas(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int ocup);
  void agregar_elementos(nodo*& principal, t_matriz tareas, int ocup);
  void mostrar_lista(nodo* principal);
  void liberar_lista(nodo*& principal);

#endif