#ifndef CASILLERO_H
#define CASILLERO_H


class Casillero {

	protected:
		int fila;
		int columna;
		char caracter;
		std::string caracterContenido;
		std::string tipo;
		std::string caracterColor;
  
		
	public:
		
		//Precondiciones: -
		//Postcondicions: Construye un objeto tipo casillero
		Casillero(int fila, int columna, char caracter);

		virtual ~Casillero(){};
		
		
		//Precondiciones: -
		//Postcondicions: Devuelve el caracter del casillero
		char obtenerCaracter();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la fila en la que se encuentra el casillero
		int obtenerFila();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la columna en la que se encuentra el casillero
		int  obtenerColumna();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el color del caracter del casillero
		std::string obtenerCaracterColor();

		virtual std::string obtenerTipo() = 0;
		virtual void establecerTipo(std::string tipo) = 0;
		virtual int obtenerCantidadMaterial() = 0;
		virtual void establecerCantidadMaterial(int cantidad) = 0;
		virtual void liberar() = 0;
		virtual void responder() = 0;
		virtual void establecerCaracterContenido(std::string caracter) = 0;
		virtual std::string obtenerCaracterContenido() = 0;
		//Precondiciones: -
		//Postcondicions: Verifica que el casillero sea construible
		bool esConstruible();
		
		//Precondiciones: -
		//Postcondicions: Verifica que el casillero sea transitable
		bool esTransitable();


    
};



#endif //CASILLERO_H
