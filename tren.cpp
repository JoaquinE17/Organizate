/*  Estructura de datos: LISTAS_ENLASADAS
Este modulo se encargara de almacenar las diferentes 'listas de tareas', permitiendo
de este modo la navegacion entre ellas.

*/
#include <iostream>
#include <cstddef>
#include <cstring> // strcpy()
#include <string>
#include <fstream> // Manejo de archivos
#include <stdio.h>
#include <windows.h>

#include "peaje.h"
#include "vagones.h"

#include "tren.h"

using namespace std;

// --- Guardar proceso ---

void guardar_itinerario(nodo* principal){
	char s_n;
    nodo* temp5 = principal;
    cout<<IDENT<<"Guardar itinerario:"<<endl;
    cout<<IDENT<<"********************************"<<endl;
    if (temp5==NULL){
        cout<<IDENT<<" Itinerario sin elementos."<<endl;
        return;
    }
    else{
    	cout<<IDENT<<"Confirmar accion s/n: ";cin>>s_n;
    	if (s_n=='n'){
    	    return;
    	}
    	std::ofstream archivo("itinerario.dat", std::ios::binary | std::ios::trunc); // trunc->(vacia)
    	archivo.close();
        do {
            guardando_lista(temp5);
            temp5 = temp5->siguiente;
        } while (temp5 != principal);
        cout<<IDENT<<" Itinerario guardado con exito."<<endl;
    }
}
void guardando_lista(const nodo* lista_final) {
	nodoAux datos_bin;
	int i;
	datos_bin.cantidad_save = lista_final->cantidad;
	datos_bin.orden_save = lista_final->orden;
	for (i=0; i<lista_final->cantidad+1;i++){
		strcpy(datos_bin.check_save[i],lista_final->check[i]);
		strcpy(datos_bin.vagon_save[i],lista_final->vagon[i]);
	}
    std::ofstream archivo("itinerario.dat", std::ios::binary | std::ios::app); // app->(agregar)
    if (archivo.is_open()) {
        archivo.write(reinterpret_cast<const char*>(&datos_bin), sizeof(nodoAux));
        archivo.close();
    } 
    else {
        std::cerr << "Error al abrir el archivo para guardar.\n";
    }
}

void recuperar_itinerario(nodo*& lista_final, int &total_tareas) {
	int contador= total_tareas-1;
    std::ifstream archivo("itinerario.dat", std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para leer.\n";
        return;
    }
    nodoAux datos_bin_aux;
    int i;
    while (archivo.read(reinterpret_cast<char*>(&datos_bin_aux), sizeof(nodoAux))) {
        cout<<IDENT<<"  "<<datos_bin_aux.vagon_save[0]<<":"<<endl;
        for (i=1; i<datos_bin_aux.cantidad_save+1; i++){
        	cout << "\t" << datos_bin_aux.check_save[i] << " " << datos_bin_aux.vagon_save[i] << endl;
        }
    }
    archivo.close();

    cout<<IDENT<<" -------------------------------\n";

    std::ifstream archivo2("itinerario.dat", std::ios::binary);
    if (!archivo2.is_open()) {
        std::cerr << "Error al abrir el archivo para leer.\n";
        return;
    }
    nodoAux datos_bin_aux2;
    while (archivo2.read(reinterpret_cast<char*>(&datos_bin_aux2), sizeof(nodoAux))) {
        cout<<IDENT<<"Agregar: "<<datos_bin_aux2.vagon_save[0]<<endl;
        contador++;
        total_tareas = contador+1;
        datos_bin_aux2.orden_save = contador;
        agregar_elementos(lista_final, datos_bin_aux2.check_save, datos_bin_aux2.vagon_save, datos_bin_aux2.cantidad_save, datos_bin_aux2.orden_save);
    }
    archivo2.close();
}

//  --- Cargar itinerario ---

void armar_itinerario(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	char op;
	do{
		system("cls");
		menu_tren();
        cout<<IDENT<<"\033[1B -------------------------------"<<endl;
        cout<<IDENT<<"\033[2AElija una opcion: ";cin>>op;
        cout<<IDENT<<"\n";
        switch(op){
            case '1':
            	cout<<IDENT<<"Agregar lista:"<<endl;
    			cout<<IDENT<<"********************************"<<endl;
                agregar_elementos(principal,no_hecho,tareas,ocup,total_tareas);
                continuar();
                break;
            case '2':
            	mostrar_lista(principal,ocup,total_tareas);
            	continuar();
            	break;
            case '3':
            	guardar_itinerario(principal);//navegar_lista(principal,op,total_tareas,ocup); //op -> variable local
            	continuar();
            	break;
            case '4':
            	liberar_lista(principal,ocup,total_tareas);
            	continuar();
            	break;
            case '5':
            	cout<<IDENT<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
            	Sleep(500);
        }
	}while(op!='5');
}

// armar_itinerario ===> [agregar_elementos]
void agregar_elementos(nodo*& principal, t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	nodo* temp6 = principal;
	if (ocup<0)
		cout<<IDENT<<" No hay elementos para agregar."<<endl;
	else{
		char s_n;
		cout<<IDENT<<" Confirmar accion s/n: ";cin>>s_n;
    	if (s_n=='n'){
    	    return;
    	}
    	else{
			nodo* nuevo = new nodo;
			int j;
			char s_n2;
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
		}
	}
}

// armar_itinerario ===> [mostrar_lista]
void mostrar_lista(nodo* principal, int ocup, int total_tareas){
	nodo* temp = principal;
   	cout<<IDENT<<"Mostrando itinerario:"<<endl;
   	cout<<IDENT<<"********************************"<<endl;
	if (total_tareas<1 && temp==NULL){
		cout<<IDENT<<" Itinerario sin elementos."<<endl;
		return;
	}
	else{
		int i;
		do {
	        cout << "  " << temp->vagon[0] << ":" << endl;
	        for (i = 1; i <= temp->cantidad; i++) {
	            cout << "\t" << temp->check[i] << " " << temp->vagon[i] << endl;
	        }
	        cout << IDENT << "********************************" << endl;
	        temp = temp->siguiente;
	    } while (temp != principal);
	}
}

// main ===> [navegar_lista]
void navegar_lista(nodo*& principal, char op, int total_tareas,int ocup){
	nodo* temp2 = principal;
	if (total_tareas<1 && temp2==NULL){
		cout<<IDENT<<"Navegando itinerario:"<<endl;
    	cout<<IDENT<<"********************************"<<endl;
		cout<<IDENT<<" Itinerario sin elementos."<<endl;
		continuar();
	}
	else{
		int i,j,n=0;
		char eleccion;
		do{
			system("cls");
			menu_main();
			cout<<IDENT<<"Elija una opcion: "<<op<<endl;
	        cout<<IDENT<<" -------------------------------"<<endl;
        	cout<<IDENT<<"Navegando itinerario:"<<endl;
    		cout<<IDENT<<"********************************"<<endl;
	        for (i=0;i<=total_tareas;i++){
	        	if (i==n){
	        		cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
	        		cout<<IDENT<<"  "<<temp2->vagon[0]<<":"<<endl;
	        		for (j=1;j<=temp2->cantidad;j++) // temp2->cantidad obtiene la cantidad de elementos en la lista
	        			cout<<IDENT<<"\t"<<temp2->check[j]<<" "<<temp2->vagon[j]<<endl;
	        	}
	        }
        	cout<<IDENT<<"- - - - - - - - - - - - - - - -\n[q]Salir [c]Marcar [v]Desmarcar"<<endl;
	        cout<<IDENT<<"********************************"<<endl;
	        cout<<IDENT<<"[a]Retroceder / [d]Avanzar: ";cin>>eleccion;
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
	        		guardar_itinerario(temp2);
	        		cout<<IDENT<<"Saliendo..."<<endl;
	        		Sleep(500);
	        		system("cls");
	        		break;
	        	default:
	        		cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
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
		menu_main();
	    cout<<IDENT<<"Elija una opcion: "<<op<<endl;
	    cout<<IDENT<<" -------------------------------"<<endl;
        cout<<IDENT<<"Marcar tarea realizada:"<<endl;
    	cout<<IDENT<<"********************************"<<endl;
    	cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<IDENT<<"  "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<IDENT<<selector<<"    "<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<IDENT<<"\t"<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
    	}
    	cout<<IDENT<<"- - - - - - - - - - - - - - - - \n [q]Salir [x]Marcar"<<endl;
        cout<<IDENT<<"********************************"<<endl;
	    cout<<IDENT<<"[w]Subir / [s]Bajar: ";
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
	        	cout<<IDENT<<"  Tarea marcada."<<endl;
	        	Sleep(500);
	        	break;
            case 'q':
                cout<<IDENT<<"Saliendo...";
                Sleep(500);
                break;
	        default:
	        	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
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
		menu_main();
	    cout<<IDENT<<"Elija una opcion: "<<op<<endl;
	    cout<<IDENT<<" -------------------------------"<<endl;
        cout<<IDENT<<"Desmarcar tarea realizada:"<<endl;
    	cout<<IDENT<<"********************************"<<endl;
    	cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<IDENT<<"  "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<IDENT<<selector<<"    "<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<IDENT<<"\t"<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
    	}
    	cout<<IDENT<<"- - - - - - - - - - - - - - - - \n [q]Salir [o]Desmarcar"<<endl;
        cout<<IDENT<<"********************************"<<endl;
	    cout<<IDENT<<"[w]Subir / [s]Bajar: ";
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
	        	cout<<IDENT<<"  Tarea desmarcada."<<endl;
	        	Sleep(500);
	        	break;
            case 'q':
                cout<<IDENT<<"Saliendo...";
                Sleep(500);
                break;
	        default:
	        	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
	    }
	    system("cls");
	}
}

void liberar_lista(nodo*& principal, int &ocup, int &total_tareas){
	char s_n;
	nodo* temp4 = principal;
	cout<<IDENT<<"Vaciar itinerario:"<<endl;
    cout<<IDENT<<"********************************"<<endl;
	if (total_tareas<1 && temp4==NULL)
		cout<<IDENT<< " Itinerario sin elementos."<<endl;
	else{
    	cout<<IDENT<<"Confirmar vaciado s/n: ";cin>>s_n;
    	if (s_n == 's'){
    		    while (principal!=NULL){
				nodo* temp = principal;
				principal = principal -> siguiente;
				temp->siguiente=NULL;
			}
			total_tareas = 0;
        	cout<<IDENT<<" Itinerario vaciado con exito.."<<endl;
    	}
    	else{
    		cout<<IDENT<<"  Vaciado cancelado..."<<endl;
            Sleep(500);
    	}
	}
}
