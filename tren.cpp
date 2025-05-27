/*  Estructura de datos: LISTAS_ENLASADAS
Este modulo se encargara de almacenar las diferentes 'listas de tareas', permitiendo
de este modo la navegacion entre ellas.
*/
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <stdio.h>

#include "peaje.h"
#include "vagones.h"

#include "tren.h"

using namespace std;

void agregar_elementos(nodo*& principal, t_matriz tareas, int ocup){
	nodo* nuevo = new nodo;
	int j;
	for (j=0;j<=ocup;j++){
		strcpy(nuevo->vagon[j],tareas[j]); 
	}
	nuevo->cantidad = ocup;
	nuevo -> siguiente = NULL;

	if (principal==NULL){
		principal = nuevo;
	}
	else{
		nodo* temp = principal;
		while (temp -> siguiente != NULL){
			temp = temp -> siguiente; 
		}
		temp -> siguiente = nuevo;
	}
}

void mostrar_lista(nodo* principal){
	nodo* temp = principal;
	int i,cont=0;
	while (temp!=NULL){
        cout<<"  "<<temp->vagon[0]<<":"<<endl;
		for (i=1;i<=temp->cantidad;i++){
			cout<<"\t"<<temp -> vagon[i]<<endl;
		}
		temp = temp -> siguiente;
	}	
}

void liberar_lista(nodo*& principal){
	while (principal!=NULL){
		nodo* temp = principal;
		principal = principal -> siguiente;
		delete temp;
	}
}
