#ifndef CASILLERO_H
#define CASILLERO_H


class Casillero {

	protected:
		int fila;
		int columna;
		char caracter;
		std::string caracter_contenido;
		std::string tipo;
		std::string caracter_color;
  
		
	public:
		
		//Precondiciones: -
		//Postcondicions: Construye un objeto tipo casillero
		Casillero(int fila, int columna, char caracter);

		virtual ~Casillero(){};
		
		
		//Precondiciones: -
		//Postcondicions: Devuelve el caracter del casillero
		char obtener_caracter();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la fila en la que se encuentra el casillero
		int obtener_fila();
		
		//Precondiciones: -
		//Postcondicions: Devuelve la columna en la que se encuentra el casillero
		int  obtener_columna();
		
		//Precondiciones: -
		//Postcondicions: Devuelve el color del caracter del casillero
		std::string obtener_caracter_color();

		virtual std::string obtener_tipo() = 0;
		virtual void establecer_tipo(std::string tipo) = 0;
		virtual int obtener_cantidad_material() = 0;
		virtual void establecer_cantidad_material(int cantidad) = 0;
		virtual void liberar() = 0;
		virtual void responder() = 0;
		virtual void establecer_caracter_contenido(std::string caracter) = 0;
		virtual std::string obtener_caracter_contenido() = 0;
		//Precondiciones: -
		//Postcondicions: Verifica que el casillero sea construible
		bool es_construible();
		
		//Precondiciones: -
		//Postcondicions: Verifica que el casillero sea transitable
		bool es_transitable();


    
};



#endif //CASILLERO_H
