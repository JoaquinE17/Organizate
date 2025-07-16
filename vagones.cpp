#include <iostream>
#include <stdio.h>
#include <cstring> //(strcpy)
#include <windows.h>
#include <fstream> //Manejo de archivos
#include <string>
#include <conio.h> //Escucha el ingreso de tecla, uso de _kbhit() y _getch()
#include <stdexcept> //Permite que el programa detecte errores y los maneje de forma estructurada, lanzando ("throw") y capturando ("catch") objetos de estas clases.

#include "vagones.h"

using namespace std;

// [1] Crear nueva lista de tareas
void crear_lista_nueva(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    t_flecha check="[_]";
    char op;
    t_h2 title_default;
    if (confirmacion()){
        ocup = 0;
        cout<<IDENT<<"  Ingrese titulo: "<<endl;
        cout<<IDENT<<"   >\n [q] Cancelar";
        cout<<IDENT<<"\033[1A\033[8D";
        fflush(stdin);
        gets(title_default);
        strcpy(tareas[ocup],title_default);
        if (*tareas[ocup]!= 'q')
            modAgregar_tr(no_hecho,tareas,ocup);
        else{
            ocup--;
            system("cls");
        }
    }
}

// [2] Previsualizar lista 
void previsualizar_lista(t_matriz2 no_hecho, t_matriz tareas, int ocup){ 
	int i;
	if (ocup<0){
		cout<<IDENT<<"Lista de tareas vacia.."<<endl;
	}
	else{
        cout<<IDENT<<"***** LISTA DE PENDIENTES ******"<<endl;
        cout<<IDENT<<"  "<<tareas[0]<<":"<<endl;
	    for(i=1;i<=ocup;i++)
	    	cout<<IDENT<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
        cout<<IDENT<<"********************************"<<endl;
	}
}

// [3] Modificar tareas 
void modificar_lista(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    t_tarea nota_m2;
	char sub_op;
	do{
        system("cls");
        menu_vagones();
        cout<<IDENT<<"\033[1B--------------------------------"<<endl;
        cout<<IDENT<<"\033[2AElija una opcion: ";cin>>sub_op;
        cout<<IDENT<<"\n";
        switch(sub_op){
            case '1':
                system("cls");
                strcpy(nota_m2,">_Agregando tarea");
                presentacion(nota_m2);
                if (ocup>=0){
                    previsualizar_lista(no_hecho,tareas,ocup);
                    cout<<IDENT<<"Ingrese nueva tarea:"<<endl;
                }
                modAgregar_tr(no_hecho,tareas,ocup);
                break;
            case '2':
            	modtarea_c(no_hecho,tareas,ocup);
            	break;
            case '3':
                system("cls");
                strcpy(nota_m2,">_Vaciando lista");
                presentacion(nota_m2);
                if (ocup>=0)
                    previsualizar_lista(no_hecho,tareas,ocup);
            	modtarea_v(no_hecho,tareas,ocup);
            	break;
            case '4':
                system("cls");
                break;
            default:
            	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
            	Sleep(500);
        }
	}while(sub_op!='4');
}

// [3_2] Vaciar lista
void modtarea_v(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    int i;
    char s_n;
    t_flecha vacio="";
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    if (confirmacion()){
        for(i=0;i<=ocup;i++){
            strcpy(no_hecho[i],vacio);
            strcpy(tareas[i],vacio);
        }
        ocup=-1;
        cout<<IDENT<<"Lista de tareas vaciada.."<<endl;
    }
}

// [3_3] Hacer cambios
void modtarea_c(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    t_tarea nota_m3;
	char op_sub2;
	do{
        system("cls");
        menu_vagones_cambios();
        cout<<IDENT<<"\033[1B--------------------------------"<<endl;
		cout<<IDENT<<"\033[2AElija una opcion: ";cin>>op_sub2;
        cout<<IDENT<<"\n";
		switch(op_sub2){
		case '1':
            system("cls");
            strcpy(nota_m3,">_Poner check");
            presentacion(nota_m3);
            modtarea_tr(no_hecho,tareas,ocup,nota_m3);
			break;
		case '2':
            system("cls");
            strcpy(nota_m3,">_Quitar check");
            presentacion(nota_m3);
			revertir_check(no_hecho,tareas,ocup,nota_m3);
			break;
        case '3':
            system("cls");
            strcpy(nota_m3,">_Corregir/Cambiar (titulo)");
            presentacion(nota_m3);
            modificar_titulo(no_hecho,tareas,ocup);
            break;
		case '4':
            system("cls");
            strcpy(nota_m3,">_Corregir/Cambiar (tarea)");
            presentacion(nota_m3);
            modificar_tarea(tareas,ocup);
            break;
        case '5':
            break;
		default:
			cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
            Sleep(500);
		}
	}while(op_sub2!='5');
}

// [3_3_1] Marcar tarea
void modtarea_tr(t_matriz2 &no_hecho, t_matriz &tareas, int ocup, t_tarea nota_m3){
    int j,i,n=1;// 'n' es la variable para mover el selector
    t_flecha selector=">>>";
    t_flecha check="[x]";
    char elegido;
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    while(elegido!='q'){
        system("cls");
        presentacion(nota_m3);
        cout<<IDENT<<"***** LISTA DE PENDIENTES ******"<<endl;
        cout<<IDENT<<"  "<<tareas[0]<<":"<<endl;
        for(i=1;i<=ocup;i++){
            if(i==n)
                cout<<IDENT<<selector<<"    "<<no_hecho[i]<<" "<<tareas[i]<<endl;
            else
                cout<<IDENT<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
        }
        cout<<IDENT<<"- - - - - - - - - -\n [q]Salir [x]Marcar"<<endl;
        cout<<IDENT<<"********************************"<<endl;
        cout<<IDENT<<"[w]Subir / [s]Bajar: ";
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
            case 'x': // en este punto cambia [_] por [x]
                for(j=0;j<=ocup;j++){
                    if(j==n)
                        strcpy(no_hecho[n],check);
                }
                break;
            case 'q':
                cout<<IDENT<<"Saliendo..."<<endl;
                Sleep(500);
                break;
            default:
                cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
        }
        system("cls");
    }
}

// [3_3_2] Desmarcar tarea
void revertir_check(t_matriz2 &no_hecho, t_matriz tareas, int ocup, t_tarea nota_m3){ 
	int j,i,n=1;// 'n' es la variable para mover el selector
    t_flecha selector=">>>";
    t_flecha check="[_]";
    char elegido;
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    while(elegido!='q'){
    	system("cls");
        presentacion(nota_m3);
        cout<<IDENT<<"***** LISTA DE PENDIENTES ******"<<endl;
        cout<<IDENT<<"  "<<tareas[0]<<":"<<endl;
        for(i=1;i<=ocup;i++){
        	if(i==n)
                cout<<IDENT<<selector<<"    "<<no_hecho[i]<<" "<<tareas[i]<<endl;
            else
            	cout<<IDENT<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
        }
        cout<<IDENT<<"- - - - - - - - - - -\n [q]Salir [o]Desmarcar"<<endl;
        cout<<IDENT<<"********************************"<<endl;
        cout<<IDENT<<"[w]Subir / [s]Bajar: ";
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
            		if(j==n)
            			strcpy(no_hecho[n],check);
            	}
            	break;
            case 'q':
                cout<<IDENT<<"Saliendo..."<<endl;
                Sleep(500);
                break;
            default:
            	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
                Sleep(500);
        }
        system("cls");
    }
}

// [3_3_3] Cambiar titulo
void modificar_titulo(t_matriz2 &no_hecho, t_matriz &tareas, int ocup){
    t_tarea nuevo_titulo;
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    previsualizar_lista(no_hecho,tareas,ocup);
    cout<<IDENT<<"Titulo actual: \n\t> "<<tareas[0]<<endl;
    cout<<IDENT<<"Nuevo titulo: \n\t> ";
    cout<<IDENT<<"\n [q] Cancelar.";
    cout<<IDENT<<"\033[1A\033[5D";
    fflush(stdin);
    gets(nuevo_titulo);
    if (*nuevo_titulo!='q'){
        strcpy(tareas[0],nuevo_titulo);
        cout<<IDENT<<"Cambio realizado.."<<endl;
        Sleep(500);
    }
}

// [3_3_4] Cambiar tarea
void modificar_tarea(t_matriz &tareas, int ocup){
	int i,j=0,orden;
	bool cambio=false;
	t_tarea nuevo_cambio;
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    cout<<IDENT<<"***** LISTA DE PENDIENTES ******"<<endl;
    cout<<IDENT<<"  "<<tareas[0]<<":"<<endl;
	for(i=1;i<=ocup;i++){
		cout<<IDENT<<"\t["<<i<<"] "<<tareas[i]<<endl;
	}
	cout<<IDENT<<"- - - - - -\n ["<<ocup+1<<"] Salir"<<endl;
    cout<<IDENT<<"********************************"<<endl;
    cout<<IDENT<<"Valor de referencia: ";cin>>orden;
    if (cin.fail()){ // Verifica si la entrada fallo
        cin.clear(); // Limpia el estado de error
        cin.ignore(1000, '\n'); // Ignora el resto del input incorrecto (Descarta hasta 1000 caracteres o hasta encontrar un salto de línea)
        orden = ocup+2;
        // LEER: las funciones uilizadas en este bloque 'if' son de la clase [cin] de la cabecera <iostream> (input estandar)
    }
    if (orden == ocup+1){
        cout<<IDENT<<"Saliendo...";
        Sleep(500);
    }
    else{
        if (orden <= ocup){
            cout<<IDENT<<"--------------------------------"<<endl;
            cout<<IDENT<<" Tarea a cambiar: \n\t> "<<tareas[orden]<<endl;
            cout<<IDENT<<" Nueva tarea: \n\t> ";
            cout<<IDENT<<"\n [q] Cancelar.";
            cout<<IDENT<<"\033[1A\033[5D";
            fflush(stdin);
            gets(nuevo_cambio);
            if (*nuevo_cambio!='q'){
                while(cambio==false){
                    if(j==orden){
                        strcpy(tareas[j],nuevo_cambio);
                        cambio=true;
                    }
                    j++;
                }
                cout<<IDENT<<"Cambio realizado.."<<endl;
                Sleep(500);
            }
        }
        else{
            cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
            Sleep(500);
        }
    	
    }
	system("cls");
}

// [3_4] Agregar tarea
void modAgregar_tr(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
    t_flecha check= "[_]";
    t_h2 title_default;
    if (ocup<0){
        cout<<IDENT<<"Lista de tareas vacia"<<endl;
        continuar();
        return;
    }
    char op='s';
    ocup++;
    while(ocup<MAX && op=='s'){
        strcpy(no_hecho[ocup],check); // [strcpy()]-> Copia el contenido de check en no_hecho[ocup]
        cout<<IDENT<<"  Tarea["<<ocup<<"]: "<<endl;
        cout<<IDENT<<"[q] Cancelar";
        cout<<"\033[1A";
        fflush(stdin); // [fflush]-> Realiza la limpieza del buffer de entrada (stdin) standar input.
        gets(tareas[ocup]); // ¨[gets]-> Lee el valor de entrada y lo almacena en el puntero espesificado 
        if (*tareas[ocup]=='q'){
            ocup--;
            system("cls");
            break;
        }
        else{
            cout<<IDENT<<"Continuar agregando s/n: ";cin>>op;
            if (op == 's'){
                ocup++;
                cout<<"\033[1A\033[2K";
            }
            else
                system("cls");
        }
    }
    if (ocup>=MAX){
        cout<<IDENT<<"La lista alcanzo su limite"<<endl;
        ocup--; // Esto es para para que no me imprima 'MAX+1' elementos (lin.56:[i<=ocup])
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
    file << "  " << tareas[0] << " " << endl;
    for(i=1;i<=ocup;i++){
    	file << "\t" << no_hecho[i] << " " << tareas[i] << endl;
    }
    file << "********************************" << endl;
    file.close();
    system("type lista_tareas.txt");
    cout<<IDENT<<"\n Continuar exportacion s/n: ";cin>>exp;
    if (exp == 's'){
        cout<<IDENT<<"\tLista guardada..."<<endl;
        system("copy lista_tareas.txt  %%USERPROFILE%\\Desktop\\ > nul 2>&1");
        Sleep(600);
    }
    system("cls");
}
