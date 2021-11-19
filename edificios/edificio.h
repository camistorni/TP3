#ifndef EDIFICIO_H
#define EDIFICIO_H

class Edificio{

	private:
		int fila;
		int columna;
		
	public:

		~Edificio();

		//Precondiciones: -
		//Postcondicions: construye un objeto edificio
		Edificio(int fila, int columna);
		
		//Precondiciones: -
		//Postcondicions: construye la memoria para un objeto edificio
		Edificio();
		
		//Precondiciones: -
		//Postcondicions: devuelve la primer coordenada del edificio
		int obtener_fila();
		
		//Precondiciones: -
		//Postcondicions: devuelve la segunda coordenada del edificio
		int obtener_columna();

};

#endif //EDIFICIO_H
