#include <iostream>
#include "ABB.h"

using namespace std;

int main(){
	ABB *abb = new ABB();
	int datos [] = {23, 12, 31, 3, 7, 15, 29, 88, 53};
	for(int i = 0; i < 9; i++)
		abb->insertarNodo(datos[i]);
	
	abb->imprimirOrdenado();
	cout << endl;
	abb->eliminarNodo(7);
	abb->imprimirOrdenado();
	cout << endl;
	abb->cerrarDiccionario();
	delete abb;
}
