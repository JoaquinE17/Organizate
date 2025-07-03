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

void construir_lista_tareas(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	char op;
	do{
		system("cls");
		cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Construye tu itinerario"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Agregar lista actual"<<endl;
        cout<<"  [2] Mostrar itinerario"<<endl;
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
            	mostrar_lista(principal,ocup,total_tareas);
            	continuar();
            	break;
            case '3':
            	navegar_lista(principal,op,total_tareas,ocup); //op -> variable local
            	break;
            case '4':
            	liberar_lista(principal,ocup,total_tareas);
            	continuar();
            	break;
            case '5':
            	cout<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<"ERROR: Ingreso invalido."<<endl;
            	Sleep(500);
        }
	}while(op!='5');
}

void agregar_elementos(nodo*& principal, t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	if (ocup<0)
		cout<<" No hay elementos para agregar."<<endl;
	else{
		char s_n;
		cout<<"Confirmar agregacion s/n: ";cin>>s_n;
    	if (s_n=='n'){
    	    return;
    	}
    	else{
			nodo* nuevo = new nodo;
			int j;
			for (j=0;j<=ocup;j++){
				strcpy(nuevo->check[j],no_hecho[j]);
				strcpy(nuevo->vagon[j],tareas[j]); 
			}
			total_tareas++;
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
			cout<< "  Lista agregada con exito.." <<endl;
		}
	}
	
}

void mostrar_lista(nodo* principal, int ocup, int total_tareas){
   	cout<<"Mostrando itinerario:"<<endl;
   	cout<<"********************************"<<endl;
	if (total_tareas<1)
		cout<<" Itinerario sin elementos."<<endl;
	else{
		nodo* temp = principal;
		int i;
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
	if (total_tareas<1){
		cout<<"Navegando itinerario:"<<endl;
    	cout<<"********************************"<<endl;
		cout<<" Itinerario sin elementos."<<endl;
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
        	cout<<"  [2] Mostrar itinerario"<<endl;
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
        	cout<<"- - - - - - - - - - - - - - - -\n[q]Salir [c]Marcar [v]Desmarcar"<<endl;
	        cout<<"********************************"<<endl;
	        cout<<"[<(a)] | [(d)>]: ";cin>>eleccion;
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
	        	case 'c':
	        		marcar_itinerario(temp2,op);
	        		break;
	        	case 'v':
	        		desmarcar_itinerario(temp2,op);
	        		break;
	        	case 'q':
	        		cout<<"Saliendo...";
	        		Sleep(500);
	        		break;
	        	default:
	        		cout<<"ERROR: Ingreso invalido."<<endl;
	        		Sleep(500);
	        }

		}while(eleccion!='q');
	}
	
}

// navegar_lista ===> [marcar_itinerario]
void marcar_itinerario(nodo*& temp2, char op){
	int j,i,n=1;// 'n' es la variable para mover el selector
	t_flecha selector=">>>";
	t_flecha chek="[x]";
	nodo* temp3 = temp2;
	char elegido;
	while(elegido!='x' && elegido!='q'){
		system("cls");
		cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Navega atravez del itinerario"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Agregar lista actual"<<endl;
        cout<<"  [2] Mostrar itinerario"<<endl;
        cout<<"  [3] Navegar itinerario"<<endl; //Provisorio
        cout<<"  [4] Vaciar itinerario"<<endl;
        cout<<"  [5] Volver [<-"<<endl;
        cout<<"\n -------------------------------"<<endl;
	    cout<<"Elija una opcion: "<<op<<endl;
	    cout<<" -------------------------------"<<endl;
        cout<<"Marcando tarea realizada:"<<endl;
    	cout<<"********************************"<<endl;
    	cout<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<"  "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<selector<<"     "<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<"\t"<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
    	}
    	cout<<"- - - - -\n[q] Salir"<<endl;
        cout<<"********************************"<<endl;
	    cout<<"w(subir)/s(bajar)/x(marcar): ";
	    cin>>elegido;
	    switch(elegido){
	        case 's':
	        	n++;
	        	if(n>temp3->cantidad)
	        		n=temp3->cantidad;
	        	break;
	        case 'w':
	        	n--;
	        	if(n<1)
	        		n=1;
	        	break;
	        case 'x': // en este punto cambia [-] por [x]
	        	for(j=0;j<=temp3->cantidad;j++){
	        		if(j==n){
	        			strcpy(temp3->check[n],chek);
	        		}
	        	}
	        	cout<<"  Tarea marcada."<<endl;
	        	Sleep(500);
	        	break;
            case 'q':
                cout<<"Saliendo...";
                Sleep(500);
                break;
	        default:
	        	cout<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
	    }
	    system("cls");
	}
}

// navegar_lista ===> [desmarcar_itinerario]
void desmarcar_itinerario(nodo*& temp2, char op){
	int j,i,n=1;// 'n' es la variable para mover el selector
	t_flecha selector=">>>";
	t_flecha chek="[_]";
	nodo* temp3 = temp2;
	char elegido;
	while(elegido!='o' && elegido!='q'){
		system("cls");
		cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Navega atravez del itinerario"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Agregar lista actual"<<endl;
        cout<<"  [2] Mostrar itinerario"<<endl;
        cout<<"  [3] Navegar itinerario"<<endl; //Provisorio
        cout<<"  [4] Vaciar itinerario"<<endl;
        cout<<"  [5] Volver [<-"<<endl;
        cout<<"\n -------------------------------"<<endl;
	    cout<<"Elija una opcion: "<<op<<endl;
	    cout<<" -------------------------------"<<endl;
        cout<<"Desmarcando tarea realizada:"<<endl;
    	cout<<"********************************"<<endl;
    	cout<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<"  "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<selector<<"     "<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<"\t"<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
    	}
    	cout<<"- - - - -\n[q] Salir"<<endl;
        cout<<"********************************"<<endl;
	    cout<<"w(subir)/s(bajar)/o(desmarcar): ";
	    cin>>elegido;
	    switch(elegido){
	        case 's':
	        	n++;
	        	if(n>temp3->cantidad)
	        		n=temp3->cantidad;
	        	break;
	        case 'w':
	        	n--;
	        	if(n<1)
	        		n=1;
	        	break;
	        case 'o': // en este punto cambia [-] por [x]
	        	for(j=0;j<=temp3->cantidad;j++){
	        		if(j==n){
	        			strcpy(temp3->check[n],chek);
	        		}
	        	}
	        	cout<<"  Tarea desmarcada."<<endl;
	        	Sleep(500);
	        	break;
            case 'q':
                cout<<"Saliendo...";
                Sleep(500);
                break;
	        default:
	        	cout<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
	    }
	    system("cls");
	}
}

void liberar_lista(nodo*& principal, int &ocup, int &total_tareas){
	char s_n;
	cout<<"Vaciar itinerario:"<<endl;
    cout<<"********************************"<<endl;
	if (total_tareas<1)
		cout<< " Itinerario sin elementos."<<endl;
	else{
    	cout<<"Confirmar vaciado s/n: ";cin>>s_n;
    	if (s_n == 's'){
    		    while (principal!=NULL){
				nodo* temp = principal;
				principal = principal -> siguiente;
				temp->siguiente=NULL;
			}
			total_tareas = 0;
        	cout<<" Itinerario vaciado con exito.."<<endl;
    	}
    	else{
    		cout<<"  Vaciado cancelado..."<<endl;
            Sleep(500);
    	}
	}
}
