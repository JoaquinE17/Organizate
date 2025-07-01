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

void construir_lista_tareas(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup){
	char op;
	int total_tareas = 0;
	do{
		system("cls");
		cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Construye tu itinerario"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Agregar lista actual"<<endl;
        cout<<"  [2] Visualizar itinerario"<<endl;
        cout<<"  [3] Navegar itinerario"<<endl; //Provisorio
        cout<<"  [4] Vaciar itinerario"<<endl;
        cout<<"  [5] Volver [<-"<<endl;
        cout<<"\n -------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
        cout<<"\033[2AElija una opcion: ";cin>>op;
        cout<<"\n";
        switch(op){
            case '1':
                agregar_elementos(principal,no_hecho,tareas,ocup,total_tareas);
                continuar();
                break;
            case '2':
            	mostrar_lista(principal,ocup);
            	continuar();
            	break;
            case '3':
            	navegar_lista(principal,op,total_tareas,ocup); //op -> variable local
            	break;
            case '4':
            	liberar_lista(principal,ocup);
            	continuar();
            	break;
            case '5':
            	cout<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
            	Sleep(500);
        }
	}while(op!='5');
}

void agregar_elementos(nodo*& principal, t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	if (ocup<0)
		cout<<"No hay elementos para agregar al itinerario."<<endl;
	else{
		char s_n;
		cout<<"Confirmar agregacion s/n: ";cin>>s_n;
    	if (s_n=='n'){
    	    return;
    	}
    	else{
			nodo* nuevo = new nodo;
			int j;
			total_tareas++;
	    	cout<<"Agregar lista al itinerario:"<<endl;
	    	cout<<"********************************"<<endl;
			for (j=0;j<=ocup;j++){
				strcpy(nuevo->check[j],no_hecho[j]);
				strcpy(nuevo->vagon[j],tareas[j]); 
			}
			nuevo->cantidad = ocup;
			nuevo->orden = total_tareas;

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
			cout<< "Lista agregada con exito.." <<endl;
		}
	}
	
}

void mostrar_lista(nodo* principal, int ocup){
	if (ocup<0)
		cout<<"Lista vacia. No hay elementos para mostrar"<<endl;
	else{
		nodo* temp = principal;
		int i;
    	cout<<"Previsualizacion (itinerario):"<<endl;
    	cout<<"********************************"<<endl;
		do {
	        cout << "  " << temp->vagon[0] << ":" << endl;
	        for (i = 1; i <= temp->cantidad; i++) {
	            cout << "\t" << temp->check[i] << " " << temp->vagon[i] << endl;
	        }
	        cout << "********************************" << endl;
	        temp = temp->siguiente;
	    } while (temp != principal);
	}
}

void navegar_lista(nodo*& principal, char op, int total_tareas,int ocup){
	if (ocup<0){
		cout<<"Lista vacia. No hay elementos en donde navegar."<<endl;
		continuar();
	}
	else{
		int i,j,n=0;
		char eleccion;
		nodo* temp2 = principal;
		do{
			system("cls");
			cout<<"********** ORGANIZATE **********"<<endl;
        	cout<<">_Navega atravez del itinerario"<<endl;
        	cout<<" -------------------------------\n"<<endl;
			cout<<"  [1] Agregar lista actual"<<endl;
        	cout<<"  [2] Visualizar itinerario"<<endl;
        	cout<<"  [3] Navegar itinerario"<<endl; //Provisorio
        	cout<<"  [4] Vaciar itinerario"<<endl;
        	cout<<"  [5] Volver [<-"<<endl;
        	cout<<"\n -------------------------------"<<endl;
	        cout<<"Elija una opcion: "<<op<<endl;
	        cout<<" -------------------------------"<<endl;
        	cout<<"Navegando itinerario:"<<endl;
    		cout<<"********************************"<<endl;
	        for (i=0;i<=total_tareas;i++){
	        	if (i==n){
	        		cout<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
	        		cout<<"  "<<temp2->vagon[0]<<":"<<endl;
	        		for (j=1;j<=temp2->cantidad;j++) // temp2->cantidad obtiene la cantidad de elementos en la lista
	        			cout<<"\t"<<temp2->check[j]<<" "<<temp2->vagon[j]<<endl;
	        	}
	        }
        	cout<<"- - - - -  \n[q] Salir"<<endl;
	        cout<<"********************************"<<endl;
	        cout<<"[<(A)] / [(D)>]: ";cin>>eleccion;
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
	
}

void liberar_lista(nodo*& principal, int &ocup){
	char s_n;
	cout<<"Vaciar itinerario:"<<endl;
    cout<<"********************************"<<endl;
	if (ocup<0)
		cout<< "Lista vacia. No hay elementos para eliminar."<<endl;
	else{
    	cout<<"Confirmar vaciado del itinerario s/n: ";cin>>s_n;
    	if (s_n == 's'){
    		    while (principal!=NULL){
				nodo* temp = principal;
				principal = principal -> siguiente;
				temp->siguiente=NULL;
			}
			ocup = -1;
        	cout<<"Itinerario vaciado con exito.."<<endl;
    	}
    	else{
    		cout<<"Vaciado cancelado...";
            Sleep(500);
    	}
	}
}
