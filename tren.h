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
	int orden;
	nodo* siguiente; // Permite enlasar nodos
	nodo* anterior; // Permite retroceso entre nodos
};

// --- Guardar Proceso ---
struct nodoAux{ 
	t_matriz vagon_save;
	t_matriz2 check_save;
	int cantidad_save;
	int orden_save;
};
void guardar_itinerario(nodo* principal);
 void guardando_lista(const nodo* lista_final);
void recuperar_itinerario(nodo*& lista_final, int &total_tareas, t_tarea nota_m1);
// ---	---

void armar_itinerario(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas);
  void agregar_elementos(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas);
  void mostrar_lista(nodo* principal);
    void mostrar_contenido(nodo* temp_aux,int n_list);
	void navegar_lista(nodo*& principal, t_tarea nota_m1, int total_tareas, int ocup);
	  void marcar_itinerario(nodo*& principal);
	  void desmarcar_itinerario(nodo*& temp2);
  void liberar_lista(nodo*& temp2,int &ocup, int &total_tareas);

#endif