// 'Modificar_tareas' presenta errores (imprime datos basura), arregrarlos
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <windows.h>
#include <fstream> //Manejo de archivos
#include <string>
#include <conio.h> //Escucha el ingreso de tecla, uso de _kbhit() y _getch()
#include <stdexcept> //Permite que tu programa detecte errores y los maneje de forma estructurada, lanzando ("throw") y capturando ("catch") objetos de estas clases.
#include "constantes.h"
#include "peaje.h"

#include "vagones.h"

using namespace std;
// [1] Crear nueva lista de tareas
void crear_lista_nueva(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){ 
    t_flecha check="[_]";
    char op;
    t_h2 title_default;
    ocup = 0;
    cout<<"  Ingrese titulo: ";
    fflush(stdin);
    gets(title_default);
    strcpy(tareas[ocup],title_default);
    modAgregar_tr(no_hecho,tareas,ocup);
}

// [2] Previsualizar lista 
void previsualizar_lista(t_matriz2 no_hecho, t_matriz tareas, int ocup){ 
	int i;
	if (ocup<0){
		cout<<"Lista de tareas vacia.."<<endl;
	}
	else{
        cout<<"********************************"<<endl;
        cout<<"  "<<tareas[0]<<":"<<endl;
	    for(i=1;i<=ocup;i++)
	    	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
        cout<<"********************************"<<endl;
	}
}

// [3] Modificar tareas 
//[...] Agregar la opcion: "Agregar tareas pendientes" y "Cambiar titulo"
void modificar_lista(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
	char sub_op;
	do{
        system("cls");
        cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Modifica/Marca/Desmarca/Agrega"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Marcar tarea realizada"<<endl;
        cout<<"  [2] Vaciar lista de tareas"<<endl;
        cout<<"  [3] Hacer cambios en la lista"<<endl;
        cout<<"  [4] Agregar tarea a la lista"<<endl;
        cout<<"  [5] Volver [<-"<<endl;
        cout<<"\n -------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
        cout<<"\033[2AElija una opcion: ";cin>>sub_op;
        cout<<"\n";
        switch(sub_op){
            case '1':
                modtarea_tr(no_hecho,tareas,ocup,sub_op);
                break;
            case '2':
            	modtarea_v(no_hecho,tareas,ocup);
            	break;
            case '3':
            	modtarea_c(no_hecho,tareas,ocup);
            	break;
            case '4':
                cout<<"Agregar tarea:"<<endl;
                previsualizar_lista(no_hecho,tareas,ocup);
                cout<<"Ingrese nueva tarea:"<<endl;
                modAgregar_tr(no_hecho,tareas,ocup);
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
	}while(sub_op!='5');
}

// [3_1] Marcar tarea realizada 
void modtarea_tr(t_matriz2 &no_hecho, t_matriz &tareas, int ocup, char sub_op){
	int j,i,n=1;// 'n' es la variable para mover el selector
	t_flecha selector=">>>";
	t_flecha check="[x]";
	char elegido;
	while(elegido!='x' && elegido!='q'){
		system("cls");
        cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Modifica/Marca/Desmarca/Agrega"<<endl;
        cout<<" -------------------------------\n"<<endl;
        cout<<"  [1] Marcar tarea realizada"<<endl;
        cout<<"  [2] Vaciar lista de tareas"<<endl;
        cout<<"  [3] Hacer cambios en la lista"<<endl;
        cout<<"  [4] Agregar tarea a la lista"<<endl;
        cout<<"  [5] Volver [<-"<<endl;
        cout<<"\n -------------------------------"<<endl;
        cout<<"Elija una opcion: "<<sub_op<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"Marcar/Check: "<<endl;
        cout<<"********************************"<<endl;
        cout<<"  "<<tareas[0]<<":"<<endl;
	    for(i=1;i<=ocup;i++){
	    	if(i==n)
	            cout<<selector<<"     "<<no_hecho[i]<<" "<<tareas[i]<<endl;
	        else
	        	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
	    }
        cout<<"- - - - - - - - \n[Q] Cancelar"<<endl;
        cout<<"********************************"<<endl;
	    cout<<"W(subir)/S(bajar)/X(marcar): ";
	    cin>>elegido;
	    switch(elegido){
	        case 's':
	        	n++;
	        	if(n>ocup)
	        		n=ocup;
	        	break;
	        case 'w':
	        	n--;
	        	if(n<1)
	        		n=1;
	        	break;
	        case 'x': // en este punto cambia [-] por [x]
	        	for(j=0;j<=ocup;j++){
	        		if(j==n){
	        			strcpy(no_hecho[n],check);
	        		}
	        	}
	        	cout<<"Tarea marcada"<<endl;
	        	Sleep(500);
	        	break;
            case 'q':
                cout<<"Cancelando...";
                Sleep(500);
                break;
	        default:
	        	cout<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
	    }
	    system("cls");
	}
}

// [3_2] Vaciar lista
void modtarea_v(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    int i;
    char s_n;
    t_flecha vacio="";
    cout<<"Vaciar lista:"<<endl;
    cout<<"********************************"<<endl;
    cout<<"Confirmar vaciado de lista s/n: ";cin>>s_n;
    if (s_n == 'n'){
        system("cls");
        return;
    }
	for(i=0;i<=ocup;i++){
		strcpy(no_hecho[i],vacio);
		strcpy(tareas[i],vacio);
	}
	ocup=-1;
	cout<<"Lista de tareas vaciada.."<<endl;
	continuar();
}

// [3_3] Hacer cambios
void modtarea_c(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
	char op_sub2;
	do{
        system("cls");
        cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Desmarcar/Modificar"<<endl;
        cout<<" -------------------------------\n"<<endl;
		cout<<"  [1] Revertir marcacion"<<endl; 
		cout<<"  [2] Modificar tarea"<<endl;
        cout<<"  [3] Modificar titulo"<<endl;
		cout<<"  [4] Volver [<-"<<endl;
        cout<<" \n-------------------------------"<<endl;
        cout<<"\033[1B -------------------------------"<<endl;
		cout<<"\033[2AElija una opcion: ";cin>>op_sub2;
        cout<<"\n";
		switch(op_sub2){
		case '1':
			revertir_check(no_hecho,tareas,ocup,op_sub2);
			break;
		case '2':
			modificar_tarea(no_hecho,tareas,ocup,op_sub2);
			break;
        case '3':
            modificar_titulo(tareas,ocup);
            break;
		case '4':
			cout<<"Saliendo.."<<endl;
			Sleep(500);
			break;
		default:
			cout<<"ERROR: Ingreso invalido."<<endl;
            Sleep(500);
		}
	}while(op_sub2!='4');
}

// [3_3_1] Quitar marcacion
void revertir_check(t_matriz2 &no_hecho, t_matriz tareas, int ocup, char op){ 
	int j,i,n=1;// 'n' es la variable para mover el selector
    t_flecha selector=">>>";
    t_flecha check="[_]";
    char elegido;
    while(elegido!='o' && elegido!='q'){
    	system("cls");
        cout<<"********** ORGANIZATE **********"<<endl;
        cout<<">_Desmarcar/Modificar"<<endl;
        cout<<" -------------------------------\n"<<endl;
        cout<<"  [1] Revertir marcacion"<<endl; 
        cout<<"  [2] Modificar tarea"<<endl;
        cout<<"  [3] Modificar titulo"<<endl;
        cout<<"  [4] Volver [<-"<<endl;
        cout<<" \n-------------------------------"<<endl;
        cout<<"Elija una opcion: "<<op<<endl;
        cout<<" -------------------------------"<<endl;
        cout<<"Quitar check: "<<endl;
        cout<<"********************************"<<endl;
        cout<<"  "<<tareas[0]<<":"<<endl;
        for(i=1;i<=ocup;i++){
        	if(i==n)
                cout<<selector<<"     "<<no_hecho[i]<<" "<<tareas[i]<<endl;
            else
            	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
        }
        cout<<"- - - - - - - - \n[Q] Cancelar"<<endl;
        cout<<"********************************"<<endl;
        cout<<"W(subir)/S(bajar)/O(desmarcar): ";
        cin>>elegido;
        switch(elegido){
            case 's':
            	n++;
            	if(n>ocup)
            		n=ocup;
            	break;
            case 'w':
            	n--;
            	if(n<1)
            		n=1;
            	break;
            case 'o': // en este punto cambia [x] por [_]
            	for(j=0;j<=ocup;j++){
            		if(j==n){
            			strcpy(no_hecho[n],check);
            		}
            	}
            	cout<<"Tarea desmarcada"<<endl;
            	Sleep(500);
            	break;
            case 'q':
                cout<<"Cancelando...";
                Sleep(500);
                break;
            default:
            	cout<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
        }
        system("cls");
    }
}

// [3_3_2] Modificar tarea
void modificar_tarea(t_matriz2 no_hecho, t_matriz &tareas, int ocup, char op){
	int i,j=0,orden;
	bool cambio=false;
	t_tarea nuevo_cambio;
    cout<<"Corregir/Cambiar (tarea):"<<endl;
    cout<<"********************************"<<endl;
    cout<<"  "<<tareas[0]<<":"<<endl;
	for(i=1;i<=ocup;i++){
		cout<<"\t["<<i<<"] "<<tareas[i]<<endl;
	}
	cout<<"- - - - - - - - \n["<<ocup+1<<"] Cancelar"<<endl;
    cout<<"********************************"<<endl;
    cout<<"Valor de referencia: ";cin>>orden;
    if (cin.fail()){ // Verifica si la entrada fallo
        cin.clear(); // Limpia el estado de error
        cin.ignore(1000, '\n'); // Ignora el resto del input incorrecto (Descarta hasta 1000 caracteres o hasta encontrar un salto de línea)
        orden = ocup+2;
        // LEER: las funciones uilizadas en este bloque 'if' son de la clase [cin] de la cabecera <iostream> (input estandar)
    }
    if (orden == ocup+1){
        cout<<"Cancelando...";
        Sleep(500);
    }
    else{
        if (orden <= ocup){
            cout<<"Modifique la tarea: "<<endl;
            cout<<"\t> ";
            fflush(stdin);
            gets(nuevo_cambio);
            while(cambio==false){
                if(j==orden){
                    strcpy(tareas[j],nuevo_cambio);
                    cambio=true;
                }
                j++;
            }
            cout<<"Cambio realizado.."<<endl;
            Sleep(500);
        }
        else{
            cout<<"ERROR: Ingreso invalido."<<endl;
            Sleep(500);
        }
    	
    }
	system("cls");
}

// [3_3_3] Modificar titulo
void modificar_titulo(t_matriz tareas, int ocup){
    t_tarea nuevo_titulo;
    cout<<"Corregir/Cambiar (titulo):"<<endl;
    cout<<"********************************"<<endl;
    cout<<"Titulo actual: \n\t> "<<tareas[0]<<endl;
    cout<<"Nuevo titulo: \n\t> ";
    cout<<"\n[Q] Cancelar.";
    cout<<"\033[1A\033[3D";
    fflush(stdin);
    gets(nuevo_titulo);
    if (*nuevo_titulo=='q'){
        cout<<"Proceso cancelado.."<<endl;
        continuar();
    }
    else
        strcpy(tareas[0],nuevo_titulo);
}

// [3_4] Agregar tarea
void modAgregar_tr(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    t_flecha check= "[_]";
    t_h2 title_default;
    char op='s';
    ocup++;
    while(ocup<MAX && op=='s'){
        strcpy(no_hecho[ocup],check); // [strcpy()]-> Copia el contenido de check en no_hecho[ocup]
        cout<<"   Tarea["<<ocup<<"]: "<<endl;
        cout<<"[Q] Cancelar.";
        cout<<"\033[1A";
        fflush(stdin); // [fflush]-> Realiza la limpieza del buffer de entrada (stdin) standar input.
        gets(tareas[ocup]); // ¨[gets]-> Lee el valor de entrada y lo almacena en el puntero espesificado 
        cancelar_ingreso(tareas,ocup);
        cout<<"Continuar agregando s/n: ";cin>>op;
        if (op == 's'){
            ocup++;
            cout<<"\033[1A\033[2K";
        }
        else
            system("cls");
    }
    if (ocup>=MAX){
        cout<<"\tLa lista alcanzo su limite"<<endl;
        ocup--; // Esto es para para qe cuando imprima no me imprima 'MAX+1' elementos (lin.56:[i<=ocup])
        continuar();
    }
    
}

// [4] Exportar lista en formato ".txt"
void exportar_tarea(t_matriz2 no_hecho, t_matriz tareas, int ocup){
    int i;
    char exp;
    t_tarea filename = "lista_tareas.txt";
    ofstream file;
    file.open(filename);
    if(!file.is_open()){
    	cerr<<"Failed to open "<<filename<<endl;
    }
    file << "********** ORGANIZATE **********" <<endl;
    for(i=0;i<=ocup;i++){
    	file << "\t" << no_hecho[i] << " " << tareas[i] << endl;
    }
    file << "********************************" << endl;
    file.close();
    system("type lista_tareas.txt");
    cout<<"\nContinuar exportacion s/n: ";cin>>exp;
    if (exp == 's'){
        cout<<"\tLista guardada..."<<endl;
        system("copy lista_tareas.txt  %%USERPROFILE%\\Desktop\\ > nul 2>&1");
        Sleep(600);
    }
    system("cls");
}
