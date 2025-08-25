#include <iostream>
#include <cstddef>
#include <cstring> // strcpy()
#include <string>
#include <fstream> // Manejo de archivos
#include <stdio.h>
#include <windows.h>

#include "tren.h"
using namespace std;

// ^^^^   ARMAR, GUARDAR Y VACIAR ITINERARIO (tren)   ^^^^
// Armar itinerario ===> [tren]
void armar_itinerario(nodo*& principal,t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	char op;
	t_tarea nota_m4;
	do{
		system("cls");
		menu_tren();
        cout<<IDENT<<"\033[1B-------------------------------"<<endl;
        cout<<IDENT<<"\033[2AElija una opcion: ";cin>>op;
        cout<<IDENT<<"\n";
        switch(op){
            case '1':
            	system("cls");
            	strcpy(nota_m4,">_Agregando lista");
    			presentacion(nota_m4);
                agregar_elementos(principal,no_hecho,tareas,ocup,total_tareas);
                continuar();
                break;
            case '2':
            	system("cls");
            	strcpy(nota_m4,">_Mostrando itinerario");
            	presentacion(nota_m4);
            	mostrar_lista(principal);
            	break;
            case '3':
            	system("cls");
            	strcpy(nota_m4,">_Guardando itinerario");
            	presentacion(nota_m4);
            	guardar_itinerario(principal);//navegar_lista(principal,op,total_tareas,ocup); //op -> variable local
            	continuar();
            	break;
            case '4':
            	system("cls");
            	strcpy(nota_m4,">_Vaciando itinerario");
            	presentacion(nota_m4);
            	liberar_lista(principal,ocup,total_tareas);
            	continuar();
            	break;
            case '5':
            	system("cls");
            	break;
            default:
            	cout<<IDENT<<"ERROR: Ingreso invalido."<<endl;
            	Sleep(500);
        }
	}while(op!='5');
}

// Agregar elemento al itinerario ===> [tren]
void agregar_elementos(nodo*& principal, t_matriz2 no_hecho, t_matriz tareas, int &ocup, int &total_tareas){
	nodo* temp6 = principal;
	if (ocup<0)
		cout<<IDENT<<"No hay elementos para agregar."<<endl;
	else{
		char s_n;
		previsualizar_lista(no_hecho,tareas,ocup);
		cout<<IDENT<<"Agregar lista? s/n: ";cin>>s_n;
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
// Mostrar titulos enumerados ===> [tren]
void mostrar_lista(nodo* principal){
	nodo* temp=principal; 
	int n_list,limit;
	if (temp==NULL){
		cout<<IDENT<<"Itinerario sin elementos."<<endl;
		return;
	}
	else{
	    cout<<IDENT<<" ------------------------------"<<endl;
		do {
	        cout<<IDENT<<"  ["<<temp->orden<<"] "<<temp->vagon[0]<<endl;
	        cout<<IDENT<<" |----------------------------|"<<endl;
	        limit = temp->orden;
	        temp = temp->siguiente;
	    } while (temp != principal);
	}
	cout<<"\033[1A";
	cout<<IDENT<<" ------------------------------"<<endl;
	cout<<IDENT<<"[0] Salir"<<endl;
	cout<<IDENT<<"--------------------------------"<<endl;
	cout<<IDENT<<"Inserte numero: ";cin>>n_list;
	if (cin.fail()){ // Verifica si la entrada fallo
        cin.clear(); // Limpia el estado de error
        cin.ignore(1000, '\n');
	}
	if (n_list>0 && n_list<=limit)
		mostrar_contenido(temp,n_list);
}
void mostrar_contenido(nodo* principal,int n_list){
    int j;
    nodo* temp_aux=principal;
    t_tarea nota_m4_2;
    system("cls");
    strcpy(nota_m4_2,">_Mostrando itinerario");
    presentacion(nota_m4_2);
    do{
        if (temp_aux->orden==n_list){
		    cout<<IDENT<<" ------------------------------"<<endl;
		    cout<<IDENT<<"  ["<<temp_aux->orden<<"] "<<temp_aux->vagon[0]<<endl;
		    cout<<IDENT<<" ------------------------------"<<endl;
            for (j=1;j<=temp_aux->cantidad;j++) // temp->cantidad obtiene la cantidad de elementos en la lista
                cout<<IDENT<<"  "<<temp_aux->check[j]<<" "<<temp_aux->vagon[j]<<endl;
            break;
        }
        temp_aux = temp_aux->siguiente;
    }while(temp_aux!=principal);
    cout<<IDENT<<" ------------------------------"<<endl;
    continuar();
    presentacion(nota_m4_2);
    mostrar_lista(principal);
}

// Guardar itinerario ===> [tren]
void guardar_itinerario(nodo* principal){
	char s_n;
    nodo* temp5 = principal;
    if (temp5==NULL){
        cout<<IDENT<<"Itinerario sin elementos."<<endl;
        return;
    }
    else{
    	cout<<IDENT<<" ------------------------------"<<endl;
		do {
	        cout<<IDENT<<"  ["<<temp5->orden<<"] "<<temp5->vagon[0]<<endl;
	        cout<<IDENT<<" |----------------------------|"<<endl;
	        temp5 = temp5->siguiente;
	    } while (temp5 != principal);
		cout<<"\033[1A";
		cout<<IDENT<<" ------------------------------"<<endl;
	    cout<<IDENT<<"--------------------------------"<<endl;
    	cout<<IDENT<<"Guardar itinerario? s/n: ";cin>>s_n;
    	if (s_n=='n'){
    	    return;
    	}
    	std::ofstream archivo("itinerario.dat", std::ios::binary | std::ios::trunc); // trunc->(vacia)
    	archivo.close();
        do {
            guardando_lista(temp5);
            temp5 = temp5->siguiente;
        } while (temp5 != principal);
        cout<<IDENT<<"\033[1AGUARDADO...                 "<<endl;
    }
}
// Guardar lista === [guardar itinerario] ===> [tren]
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
// Vaciado Itinerario ===> [tren]
void liberar_lista(nodo*& principal, int &ocup, int &total_tareas){
	char s_n;
	nodo* temp4 = principal;
	if (temp4==NULL)
		cout<<IDENT<< "Itinerario sin elementos."<<endl;
	else{
		cout<<IDENT<<" ------------------------------"<<endl;
		do {
	        cout<<IDENT<<"  ["<<temp4->orden<<"] "<<temp4->vagon[0]<<endl;
	        cout<<IDENT<<" |----------------------------|"<<endl;
	        temp4 = temp4->siguiente;
	    } while (temp4 != principal);
		cout<<"\033[1A";
		cout<<IDENT<<" ------------------------------"<<endl;
	    cout<<IDENT<<"--------------------------------"<<endl;
    	cout<<IDENT<<"Confirmar vaciado s/n: ";cin>>s_n;
    	if (s_n == 's'){
    		    while (principal!=NULL){
				nodo* temp = principal;
				principal = principal -> siguiente;
				temp->siguiente=NULL;
			}
			total_tareas = 0;
			cout<<IDENT<<"\033[1AVACIADO...                 "<<endl;
    	}
	}
}


// ^^^^   RECUPERAR Y NAVEGAR ITINERARIO (main)   ^^^^
// Recuperar itinerario guardado ===> [main]
void recuperar_itinerario(nodo*& lista_final, int &total_tareas, t_tarea nota_m1) {
	int contador= total_tareas-1;
    std::ifstream archivo2("itinerario.dat", std::ios::binary);
    if (!archivo2.is_open()) {
        std::cerr << "Error al abrir el archivo para leer.\n";
        return;
    }
    nodoAux datos_bin_aux2;
    while (archivo2.read(reinterpret_cast<char*>(&datos_bin_aux2), sizeof(nodoAux))) {
    	system("cls");
    	presentacion(nota_m1);
        contador++;
        total_tareas = contador+1;
        datos_bin_aux2.orden_save = contador;
        agregar_elementos(lista_final, datos_bin_aux2.check_save, datos_bin_aux2.vagon_save, datos_bin_aux2.cantidad_save, datos_bin_aux2.orden_save);
    }
    archivo2.close();
}
// Navegar itinerario ===> [main]
void navegar_lista(nodo*& principal, t_tarea nota_m1, int total_tareas,int ocup){
	nodo* temp2 = principal;
	if (temp2==NULL){
		cout<<IDENT<<" Itinerario sin elementos."<<endl;
		continuar();
	}
	else{
		int i,j,n=0;
		char eleccion;
		do{
			system("cls");
			presentacion(nota_m1);
	        for (i=0;i<=total_tareas;i++){
	        	if (i==n){
	        		cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
	        		cout<<IDENT<<" "<<temp2->vagon[0]<<":"<<endl;
	        		for (j=1;j<=temp2->cantidad;j++) // temp2->cantidad obtiene la cantidad de elementos en la lista
	        			cout<<IDENT<<"  "<<temp2->check[j]<<" "<<temp2->vagon[j]<<endl;
	        	}
	        }
        	cout<<IDENT<<"- - - - - - - - - - - - - - - -\n [q]Salir [c]Marcar [v]Desmarcar"<<endl;
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
	        		marcar_itinerario(temp2);
	        		break;
	        	case 'v':
	        		desmarcar_itinerario(temp2);
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
// Marcar itinerario ===> [Navegar itinerario] ===> [main]
void marcar_itinerario(nodo*& temp2){
	int j,i,n=1;// 'n' es la variable para mover el selector
	t_flecha selector=">>";
	t_flecha chek="[x]";
	t_flecha proceso="[p]";
	nodo* temp3 = temp2;
	char elegido;
	t_tarea nota_6_M;
	strcpy(nota_6_M,">_Marcar tarea");
	while(elegido!='x' && elegido!='q' && elegido!='p'){
		system("cls");
		presentacion(nota_6_M);
    	cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<IDENT<<" "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<IDENT<<selector<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<IDENT<<"  "<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
    	}
    	cout<<IDENT<<"- - - - - - - - - - - - - - - - \n [q]Salir [x]Hecho [p]En proceso"<<endl;
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
	        case 'p':
	        	for(j=0;j<=temp3->cantidad;j++){
	        		if(j==n){
	        			strcpy(temp3->check[n],proceso);
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
// Desmarcar itinerario ===> [Navegar itinerario] ===> [main]
void desmarcar_itinerario(nodo*& temp2){
	int j,i,n=1;// 'n' es la variable para mover el selector
	t_flecha selector=">>";
	t_flecha chek="[_]";
	nodo* temp3 = temp2;
	char elegido;
	t_tarea nota_6_D;
	strcpy(nota_6_D,">_Desmarcar tarea");
	while(elegido!='o' && elegido!='q'){
		system("cls");
		presentacion(nota_6_D);
    	cout<<IDENT<<"*********** LISTA 0"<<temp2->orden<<" ***********"<<endl;
    	cout<<IDENT<<" "<<temp3->vagon[0]<<":"<<endl;
    	for (i=1; i<=temp3->cantidad; i++){
    		if (i==n)
    			cout<<IDENT<<selector<<temp3->check[i]<<" "<< temp3->vagon[i]<<endl;
    		else
    			cout<<IDENT<<"  "<<temp3->check[i]<<" "<<temp3->vagon[i]<<endl;
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
