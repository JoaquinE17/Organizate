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
	int total_tareas = 0;
	do{
		system("cls");
		cout<<"******* -CONSTRUIR LISTA *******"<<endl;
		cout<<"  [1] Agregar tarea a la lista"<<endl;
        cout<<"  [2] Visualizar lista"<<endl;
        cout<<"  [3] Navegar lista"<<endl; //Provisorio
        cout<<"  [4] Volver [<-"<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
        cout<<"\033[2AElija una opcion: ";cin>>op;
        cout<<"\n";
        switch(op){
            case '1':
                agregar_elementos(principal,no_hecho,tareas,ocup,total_tareas);
                cout<<"Elemento agragado.."<<endl;
                continuar();
                break;
            case '2':
            	mostrar_lista(principal);
            	continuar();
            	break;
            case '3':
            	navegar_lista(principal,op,total_tareas); //op -> variable local
            	break;
            case '4':
            	cout<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
            	Sleep(500);
        }
	}while(op!='4');
}

void agregar_elementos(nodo*& principal, t_matriz2 no_hecho, t_matriz tareas, int ocup, int &total_tareas){
	nodo* nuevo = new nodo;
	int j;
	for (j=0;j<=ocup;j++){
		strcpy(nuevo->check[j],no_hecho[j]);
		strcpy(nuevo->vagon[j],tareas[j]); 
	}
	nuevo->cantidad = ocup;

	if (principal==NULL){
		principal = nuevo;
		principal->siguiente = principal; // Se apunta asi misma
        principal->anterior = principal;
	}
	else{
		nodo* ultimo = principal->anterior;

        // Enlazar nuevo nodo al final
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;

        // Cerrar el ciclo
        nuevo->siguiente = principal;
        principal->anterior = nuevo;
    }
	total_tareas++;
}

void mostrar_lista(nodo* principal){
	nodo* temp = principal;
	int i;
	cout<<"********** ORGANIZATE **********" <<endl;
	do {
        cout << "  " << temp->vagon[0] << ":" << endl;
        for (i = 1; i <= temp->cantidad; i++) {
            cout << "\t" << temp->check[i] << " " << temp->vagon[i] << endl;
        }
        cout << "********************************" << endl;
        temp = temp->siguiente;
    } while (temp != principal);
	
}

void navegar_lista(nodo*& principal, char op, int total_tareas){
	int i,j,n=0;
	char eleccion;
	nodo* temp2 = principal;
	do{
		system("cls");
		cout<<"******* -CONSTRUIR LISTA *******"<<endl;
		cout<<"  [1] Agregar tarea a la lista"<<endl;
        cout<<"  [2] Visualizar lista"<<endl;
        cout<<"  [3] Navegar lista"<<endl; //Provisorio
        cout<<"  [4] Volver [<-"<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"Elija una opcion: "<<op<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"\n";
        cout<<"********** ORGANIZATE **********" <<endl;
        for (i=0;i<=total_tareas;i++){
        	if (i==n){
        		cout<<"  "<<temp2->vagon[0]<<":"<<endl;
        		for (j=1;j<=temp2->cantidad;j++)
        			cout<<"\t"<<temp2->check[j]<<" "<<temp2->vagon[j]<<endl;
        	}
        }
        cout << "********************************" << endl;
        cout<<"\n";
        cout<<"D(avansar)/A(retroseder)/Q(Salir): ";cin>>eleccion;
        switch(eleccion){
        	case 'd':
        		n++;
        		if (n>total_tareas)
        			n=total_tareas;
        		temp2 = temp2->siguiente;
        		break;
        	case 'a':
        		n--;
        		if (n<1)
        			n=0;
        		temp2 = temp2->anterior;
        		break;
        	case 'q':
        		cout<<"Cancelando...";
        		Sleep(500);
        		break;
        	default:
        		cout<<"ERROR: Ingreso invalido."<<endl;
        		Sleep(500);
        }

	}while(eleccion!='q');
}

void liberar_lista(nodo*& principal){
	while (principal!=NULL){
		nodo* temp = principal;
		principal = principal -> siguiente;
		delete temp;
	}
}
