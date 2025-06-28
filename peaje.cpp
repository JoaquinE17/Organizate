#include <iostream>
#include <windows.h>

#include "peaje.h"

using namespace std;

void cancelar_ingreso(t_matriz tareas, int &ocup){
    char letra = 'q';
    if (*tareas[ocup] == letra){
        ocup--;
        cout<<"Proceso cancelado.."<<endl;
        Sleep(500);
    }
    else{
        return;
    }
}

void continuar(){
	char conti;
	cout<<"Continuar [c]: ";cin>>conti;
	system("cls");
}

void HabilitarAnsiEscapeCodes() { // Habilitar codigo ASCII
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
