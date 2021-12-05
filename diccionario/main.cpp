#include <iostream>
#include "ABB.h"

using namespace std;

int main(){
	ABB *abb = new ABB();
	string clave[] = {"escuela", "aserradero", "fabrica"};
	string datos [] = {"5 1 3", "4 7 3", "33 4 34"};
	for(int i = 0; i < 3; i++)
		abb->insertarNodo(clave[i], datos[i]);
	
	abb->imprimirOrdenado();
	cout << endl;
	abb->eliminarNodo("escuela");
	abb->imprimirOrdenado();
	cout << endl;
	
	abb->cerrarDiccionario();
	delete abb;
}