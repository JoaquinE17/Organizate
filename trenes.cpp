#include <iostream>
#include <stdio.h>
#include <cstring>
#include <windows.h>
#include <fstream> //Manejo de archivos
#include <string>
#include <conio.h> //Escucha el ingreso de tecla, uso de _kbhit() y _getch()
#include "constantes.h"
#include "peaje.h"

#include "trenes.h"

using namespace std;

void agregar_titulo(t_h2 &titulo){
    char op;
    t_h2 title_default = "Lista de tareas:";
    cout<<"Insetar titulo s/n: ";cin>>op;
    if (op == 's'){
        cout<<"  > ";
        fflush(stdin);
        gets(titulo);
    }
}

// [1] Agregar tarea
void ingresar_tarea(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup, t_h2 &titulo){ 
	t_flecha check="[_]";
	if (ocup==MAX){
		cout<<"Las lista alcanzo su limite"<<endl;
	}
	else{
		ocup++;
		strcpy(no_hecho[ocup],check); // [strcpy()]-> Copia el contenido de check en no_hecho[ocup]
        agregar_titulo(titulo);
		cout<<"\t> \n[q]Cancelar";
        cout<<"\033[1A";
		fflush(stdin); // [fflush]-> Realiza la limpieza del buffer de entrada (stdin) standar input.
		gets(tareas[ocup]); // ¨[gets]-> Lee el valor de entrada y lo almacena en el puntero espesificado 
        cancelar_ingreso(tareas,ocup);
	}
	system("cls");
}

// [2] Mostrar lista 
void mostrar_tarea(t_matriz2 no_hecho, t_matriz tareas, int ocup){ 
	int i;
	if (ocup<0){
		cout<<"Lista de tareas vacia.."<<endl;
		continuar();
	}
	else{
		cout<<"\n";
	    for(i=0;i<=ocup;i++)
	    	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
	    cout<<" "<<endl;
	    continuar();
	}
}
// [3] Modificar tareas de la lista 
void modificar_tarea(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
	char sub_op;
	system("cls");
	do{
        cout<<"********** -MODIFICAR **********"<<endl;
		cout<<"  [1] Marcar tarea realizada"<<endl;
        cout<<"  [2] Vaciar lista de tareas"<<endl;
        cout<<"  [3] Hacer cambios en la lista"<<endl;
        cout<<"  [4] Volver [<-"<<endl;
        cout<<" -------------------------------"<<endl;
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
            	cout<<"Volviendo al menu principal.."<<endl;
            	Sleep(500);
            	system("cls");
            	break;
            default:
            	cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
            	Sleep(500);
        }
	}while(sub_op!='4');
}
    // [3_1] Marcar tarea realizada 
    void modtarea_tr(t_matriz2 &no_hecho, t_matriz &tareas, int ocup, char sub_op){
    	int j,i,n=0;// 'n' es la variable para mover el selector
    	t_flecha selector=">>>";
    	t_flecha check="[x]";
    	char elegido;
    	while(elegido!='x' && elegido!='q'){
    		system("cls");
    		cout<<"[1] Marcar tarea realizada"<<endl;
            cout<<"[2] Vaciar lista de tareas"<<endl;
            cout<<"[3] Hacer cambios en la lista"<<endl;
            cout<<"[4] Volver [<-"<<endl;
            cout<<"Elija una opcion: "<<sub_op<<endl;
            cout<<"\n";
    	    for(i=0;i<=ocup;i++){
    	    	if(i==n)
    	            cout<<selector<<"     "<<no_hecho[i]<<" "<<tareas[i]<<endl;
    	        else
    	        	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
    	    }
    	    cout<<"\n";
    	    cout<<"W(subir)/S(bajar)/X(marcar)/Q(cancelar): ";
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
    	        		n=0;
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
    	        	cout<<"ERROR"<<endl;
    	    }
    	    system("cls");
    	}
    }
    // [3_2] Vaciar lista
    void modtarea_v(t_matriz2 &no_hecho, t_matriz &tareas, int &ocup){
        int i;
        char s_n;
        t_flecha vacio="";
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
    	system("cls");
    	do{
    		cout<<"[1] Revertir marcacion de tarea"<<endl; 
    		cout<<"[2] Corregir una tarea de la lista"<<endl;
    		cout<<"[3] Volver [<-"<<endl;
    		cout<<"Elija una opcion: ";cin>>op_sub2;
    		switch(op_sub2){
    		case '1':
    			revertir_check(no_hecho,tareas,ocup,op_sub2);
    			break;
    		case '2':
    			corregir_tarea(no_hecho,tareas,ocup,op_sub2);
    			break;
    		case '3':
    			cout<<"Saliendo.."<<endl;
    			Sleep(500);
    			break;
    		default:
    			cout<<"ERROR: Ingreso invalido. Ingrese nuevamente."<<endl;
    		}
    	}while(op_sub2!='3');
        system("cls");
    }
        // [3_3_1] Quitar marcacion
        void revertir_check(t_matriz2 &no_hecho, t_matriz tareas, int ocup, char op){ 
        	int j,i,n=0;// 'n' es la variable para mover el selector
    	    t_flecha selector=">>>";
    	    t_flecha check="[_]";
    	    char elegido;
    	    while(elegido!='x' && elegido!='q'){
    	    	system("cls");
                cout<<"Seleccione la tarea a desmarcar: "<<endl;
                cout<<"\n";
    	        for(i=0;i<=ocup;i++){
    	        	if(i==n)
    	                cout<<selector<<"     "<<no_hecho[i]<<" "<<tareas[i]<<endl;
    	            else
    	            	cout<<"\t"<<no_hecho[i]<<" "<<tareas[i]<<endl;
    	        }
    	        cout<<"\n";
    	        cout<<"W(subir)/S(bajar)/X(desmarcar)/Q(cancelar): ";
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
    	            		n=0;
    	            	break;
    	            case 'x': // en este punto cambia [_] por [x]
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
    	            	cout<<"ERROR"<<endl;
    	        }
    	        system("cls");
    	    }
        }
        // [3_3_2] Corregir tarea
        void corregir_tarea(t_matriz2 no_hecho, t_matriz &tareas, int ocup, char op){
        	int i,j=0,orden;
        	bool cambio=false;
        	t_tarea nuevo_cambio;
            cout<<"\n";
        	for(i=0;i<=ocup;i++){
        		cout<<"\t["<<i<<"]"<<tareas[i]<<endl;
        	}
        	cout<<"\n["<<ocup+1<<"] Cancelar\nInserte el valor de referencia: ";cin>>orden;
            if (orden == ocup+1){
                cout<<"Cancelando...";
                Sleep(500);
            }
            else{
            	cout<<"Acontinuacion modifique la tarea: "<<endl;
            	cout<<"\t>";cin>>nuevo_cambio;
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
        	system("cls");
        }
// [4] Exportar lista en formato ".txt"
void exportar_tarea(t_matriz2 no_hecho, t_matriz tareas, int ocup, t_h2 titulo){
    int i;
    char exp;
    t_tarea filename = "lista_tareas.txt";
    ofstream file;
    file.open(filename);
    if(!file.is_open()){
    	cerr<<"Failed to open "<<filename<<endl;
    }
    file << "********** ORGANIZATE **********" <<endl;
    file << " _" << titulo << ":" << endl;
    for(i=0;i<=ocup;i++){
    	file << "\t" << no_hecho[i] << " " << tareas[i] << endl;
    }
    file << "********************************" << endl;
    file.close();
    system("type lista_tareas.txt");
    cout<<"\nContinuar exportacion s/n: ";cin>>exp;
    if (exp == 's'){
        cout<<"\tLista guardada..."<<endl;
        system("copy C:\\Users\\joako\\Desktop\\proyectos\\proyecto_3\\lista_tareas.txt  C:\\Users\\joako\\Desktop\\ > nul");
        Sleep(600);
    }
    system("cls");
}

/* 
	copy C:\Users\joako\Desktop\proyectos\proyecto_3\lista_tareas.txt C:\Users\joako\Desktop\
*/
