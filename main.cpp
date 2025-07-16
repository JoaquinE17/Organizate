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
    t_tarea nota_m1;

    nodo* lista_final = NULL;

    int indice=-1, total_tareas=0;
    char op,op2;
    system("cls");
    desactivarMaximizar();
    system("mode con: cols=34 lines=23"); // [lines=35] Reedimenciona la ventana (consola)
    SetConsoleTitle("Organizate"); // Renombra la ventana

    do{
        HabilitarAnsiEscapeCodes();
        menu_main();
        cout<<IDENT<<"\033[1B--------------------------------"<<endl;
    	cout<<IDENT<<"\033[2AElija una opcion: ";cin>>op;
        cout<<IDENT<<"\n";
    	switch(op){
    	    case '1': 
                system("cls");
                strcpy(nota_m1,">_Creando lista");
                presentacion(nota_m1);
    	    	crear_lista_nueva(no_hecho,pendientes,indice);
    	    	break;
    	    case '2':
                system("cls");
                strcpy(nota_m1,">_Mostrando lista");
                presentacion(nota_m1);
    	    	previsualizar_lista(no_hecho,pendientes,indice);
                continuar();
    	    	break;
    	    case '3':
    	    	modificar_lista(no_hecho,pendientes,indice);
    	    	break;
    	    case '4':
                armar_itinerario(lista_final,no_hecho,pendientes,indice,total_tareas);
    	    	break;
    	    case '5':
                system("cls");
                strcpy(nota_m1,">_Recuperando listas");
                presentacion(nota_m1);
                recuperar_itinerario(lista_final,total_tareas,nota_m1);
                continuar();
                break;
            case '6':
                system("cls");
                strcpy(nota_m1,">_Navegando itinerario");
                presentacion(nota_m1);
                navegar_lista(lista_final,nota_m1,total_tareas,indice);
                break;
            case '7':
                cout<<IDENT<<"Saliendo..\n"<<endl;
                Sleep(500);
                break;
    	    default:
    	    	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
                continuar();
    	}
    }while(op!='7');
    system("mode con: cols=80 lines=25");
}
