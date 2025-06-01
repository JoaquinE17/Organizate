// ALMACENAMIENTO DE TAREAS - LISTAS_ENLASADAS
#ifndef TREN_H
#define TREN_H

#include "constantes.h"
#include "peaje.h"
#include "vagones.h"

typedef t_flecha t_matriz2[MAX];
typedef t_tarea t_matriz[MAX];
typedef char t_h2[20];
struct nodo{ 
	t_matriz vagon;
	t_matriz2 check;
	int cantidad;
	nodo* siguiente; // Permite enlasar nodos
	nodo* anterior; // Permite retroceso entre nodos
};

void construir_lista_tareas(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int ocup);
  void agregar_elementos(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int ocup, int &total_tareas);
  void mostrar_lista(nodo* principal);
	void navegar_lista(nodo*& principal, char op, int total_tareas);
  void liberar_lista(nodo*& principal);

#endif