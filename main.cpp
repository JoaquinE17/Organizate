#include <iostream>
#include <stdio.h>
#include <cstring>
#include <windows.h>
#include <fstream> //Manejo de archivos
#include <string>
#include <conio.h> //Escucha el ingreso de tecla, uso de _kbhit() y _getch()

#include "constantes.h"
#include "peaje.h"
#include "vagones.h"
#include "tren.h"
/* NO OLVIDARSE: 
_Al momento de crear un nuevo '.cpp', este debe ser agregado manualmente dentro de [compilar.bat], 
de esta manera se compilaran todos los '.cpp' en uno solo, que sera un '.exe' (ejecutable).
_En los archivos '.h' se deberan colocar solo las referencias de las funciones, mientrar que en los '.cpp' 
se colocaran los codigos correspondientes a esas funciones. Los '.h' que requieren '.cpp' deberan nombrarse 
de la misma forma, ejemplo:[pepito.h - pepito.cpp]
 */
using namespace std;

typedef char t_flecha[4];
typedef char t_tarea[30];
typedef char t_h2[20];
typedef t_tarea t_matriz[MAX];
typedef t_flecha t_matriz2[MAX];



int main(int argc, char *argv[]){
    t_matriz pendientes;
    t_matriz2 no_hecho;
    t_h2 titulo;

    nodo* lista_final = NULL;

    int indice=-1;
    char op,op2;
    do{
        HabilitarAnsiEscapeCodes();
        cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Organiza tus tareas pendientes"<<endl;
        cout<<" -------------------------------\n"<<endl;
    	cout<<"  [1] Crear nueva lista "<<endl;
    	cout<<"  [2] Previsualizar lista"<<endl;
    	cout<<"  [3] Modificar lista"<<endl;
    	cout<<"  [4] Exportar tarea actual"<<endl;
    	cout<<"  [5] Construir itinerario"<<endl;
        cout<<"  [6] Finalizar programa"<<endl;
        cout<<"\n -------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
    	cout<<"\033[2AElija una opcion: ";cin>>op;
        cout<<"\n";
    	switch(op){
    	    case '1': 
    	    	crear_lista_nueva(no_hecho,pendientes,indice);
    	    	break;
    	    case '2':
                cout<<"Previsualizacion (lista):"<<endl;
    	    	previsualizar_lista(no_hecho,pendientes,indice);
                continuar();
    	    	break;
    	    case '3':
    	    	modificar_lista(no_hecho,pendientes,indice);
    	    	break;
    	    case '4':
                cout<<endl;
    	    	exportar_tarea(no_hecho,pendientes,indice);
    	    	break;
    	    case '5':
                construir_lista_tareas(lista_final,no_hecho,pendientes,indice);
                break;
            case '6':
                cout<<"Saliendo..\n"<<endl;
                Sleep(500);
                break;
    	    default:
    	    	cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
                continuar();
    	}
    }while(op!='6');
}
