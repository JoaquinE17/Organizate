#include <iostream>
#include <windows.h>

#include "peaje.h"

using namespace std;

void cancelar_ingreso(t_matriz tareas, int &ocup){
    char letra = 'q';
    if (*tareas[ocup] == letra){
        ocup--;
        cout<<IDENT<<"Proceso cancelado.."<<endl;
        Sleep(500);
    }
    else{
        return;
    }
}

void continuar(){
	char conti;
    cout<<IDENT<<"--------------------------------"<<endl;
	cout<<IDENT<<"Continuar [c]: ";cin>>conti;
	system("cls");
}

void HabilitarAnsiEscapeCodes() { // Habilitar codigo ASCII
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void desactivarMaximizar() {
    HWND consoleWindow = GetConsoleWindow();
    LONG estilo = GetWindowLong(consoleWindow, GWL_STYLE);
    estilo &= ~WS_MAXIMIZEBOX;  // Quita el botón de maximizar
    estilo &= ~WS_SIZEBOX;      // Quita la capacidad de redimensionar con bordes
    SetWindowLong(consoleWindow, GWL_STYLE, estilo);
}

void presentacion(t_tarea nota){
    cout<<IDENT<<"--------------------------------"<<endl; 
    cout<<IDENT<<nota<<endl;
    cout<<IDENT<<"--------------------------------"<<endl;
}

bool confirmacion(){
    char s_n;
    cout<<IDENT<<"Confirmar accion s/n: ";cin>>s_n;
    if (s_n=='s')
        return true;
    else{
        system("cls");
        return false;
    }
}

void menu_main(){
    cout<<IDENT<<"********** ORGANIZATE **********"<<endl;
        cout<<IDENT<<">_Organiza tus tareas pendientes"<<endl;
        cout<<IDENT<<"--------------------------------\n"<<endl;
        cout<<IDENT<<"  [1] Crear nueva lista "<<endl;
        cout<<IDENT<<"  [2] Mostar lista"<<endl;
        cout<<IDENT<<"  [3] Modificar lista"<<endl;
        cout<<IDENT<<"  ------------------------"<<endl;
        cout<<IDENT<<"  [4] Armar itinerario"<<endl;
        cout<<IDENT<<"  [5] Recuperar itinerario"<<endl; // Agregar esta funcion
        cout<<IDENT<<"  [6] Navegar itinerario"<<endl; // Agregar esta funcion
        cout<<IDENT<<"\n [7] Finalizar programa"<<endl;
        cout<<IDENT<<"--------------------------------"<<endl;
}

void menu_vagones(){
    cout<<IDENT<<"--------------------------------"<<endl;
    cout<<IDENT<<">_Agregar/Modificar/Vaciar"<<endl;
    cout<<IDENT<<"--------------------------------\n"<<endl;
    cout<<IDENT<<"  [1] Agregar tarea a la lista"<<endl;
    cout<<IDENT<<"  [2] Hacer cambios en la lista"<<endl;
    cout<<IDENT<<"  [3] Vaciar lista de tareas"<<endl;  
    cout<<IDENT<<"\n [4] Volver [<-"<<endl; 
    cout<<IDENT<<"--------------------------------"<<endl;
}

void menu_vagones_cambios(){
    cout<<IDENT<<"--------------------------------"<<endl;
    cout<<IDENT<<">_Marcar/Desmarcar/Modificar"<<endl;
    cout<<IDENT<<"--------------------------------\n"<<endl;
    cout<<IDENT<<"  [1] Marcar tarea"<<endl;
    cout<<IDENT<<"  [2] Desmarcar tarea"<<endl;
    cout<<IDENT<<"  [3] Cambiar titulo"<<endl;
    cout<<IDENT<<"  [4] Cambiar tarea"<<endl;
    cout<<IDENT<<"\n [5] Volver [<-"<<endl;
    cout<<IDENT<<"--------------------------------"<<endl;
}

void menu_tren(){
    cout<<IDENT<<"--------------------------------"<<endl;
    cout<<IDENT<<">_Arma tu itinerario"<<endl;
    cout<<IDENT<<"--------------------------------\n"<<endl;
    cout<<IDENT<<"  [1] Agregar lista actual"<<endl;
    cout<<IDENT<<"  [2] Mostrar itinerario"<<endl;
    cout<<IDENT<<"  [3] Guardar itinerario"<<endl; //Provisorio
    cout<<IDENT<<"  [4] Vaciar itinerario"<<endl;
    cout<<IDENT<<"\n [5] Volver [<-"<<endl;
    cout<<IDENT<<"--------------------------------"<<endl;
}