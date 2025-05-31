/*  Estructura de datos: LISTAS_ENLASADAS
Este modulo se encargara de almacenar las diferentes 'listas de tareas', permitiendo
de este modo la navegacion entre ellas.
*/
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <stdio.h>
#include <windows.h>

#include "peaje.h"
#include "vagones.h"

#include "tren.h"

using namespace std;

void construir_lista_tareas(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int ocup){
	char op;
	do{
		system("cls");
		cout<<"******* -CONSTRUIR LISTA *******"<<endl;
		cout<<"  [1] Agregar tarea a la lista"<<endl;
        cout<<"  [2] Visualizar lista"<<endl;
        cout<<"  [3] Volver [<-"<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
        cout<<"\033[2AElija una opcion: ";cin>>op;
        cout<<"\n";
        switch(op){
            case '1':
                agregar_elementos(principal,tareas,ocup);
                cout<<"Elemento agragado.."<<endl;
                continuar();
                break;
            case '2':
            	mostrar_lista(principal);
            	continuar();
            	break;
            case '3':
            	cout<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
            	Sleep(500);
        }
	}while(op!='3');
}

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
	cout<<"********** ORGANIZATE **********" <<endl;
	while (temp!=NULL){
        cout<<"  "<<temp->vagon[0]<<":"<<endl;
		for (i=1;i<=temp->cantidad;i++){
			cout<<"\t"<<temp -> vagon[i]<<endl;
		}
		temp = temp -> siguiente;
		cout<<"********************************"<<endl;
	}	
}

void liberar_lista(nodo*& principal){
	while (principal!=NULL){
		nodo* temp = principal;
		principal = principal -> siguiente;
		delete temp;
	}
}
