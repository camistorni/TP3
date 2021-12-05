CC = g++ -Wall -Werror -Wconversion
OBJS = main.o mapa.o utilesMenu.o materiales.o jugador.o juego.o edificio.o casilleroConstruible.o casilleroInaccesible.o casilleroTransitable.o casillero.o CaminoMinimo.o Dijkstra.o Grafo.o Vertice.o

andypolis: $(OBJS)
	$(CC) -o andypolis $(OBJS)
	rm -f *.o *~ 

main.o: src/main.cpp
	$(CC) -o main.o -c src/main.cpp

mapa.o: src/mapa/mapa.cpp
	$(CC) -o mapa.o -c src/mapa/mapa.cpp

utilesMenu.o: src/menu/utilesMenu.cpp
	$(CC) -o utilesMenu.o -c src/menu/utilesMenu.cpp

materiales.o: src/materiales/materiales.cpp
	$(CC) -o materiales.o -c src/materiales/materiales.cpp

juego.o: src/juego/juego.cpp
	$(CC) -o juego.o -c src/juego/juego.cpp

jugador.o: src/jugadores/jugador.cpp
	$(CC) -o jugador.o -c src/jugadores/jugador.cpp	

edificio.o: src/edificios/edificio.cpp
	$(CC) -o edificio.o -c src/edificios/edificio.cpp

casilleroConstruible.o: src/mapa/casilleros/casilleroConstruible/casilleroConstruible.cpp
	$(CC) -o casilleroConstruible.o -c src/mapa/casilleros/casilleroConstruible/casilleroConstruible.cpp

casilleroInaccesible.o: src/mapa/casilleros/casilleroInaccesible/casilleroInaccesible.cpp
	$(CC) -o casilleroInaccesible.o -c src/mapa/casilleros/casilleroInaccesible/casilleroInaccesible.cpp

casilleroTransitable.o: src/mapa/casilleros/casilleroTransitable/casilleroTransitable.cpp
	$(CC) -o casilleroTransitable.o -c src/mapa/casilleros/casilleroTransitable/casilleroTransitable.cpp

casillero.o: src/mapa/casilleros/casillero.cpp
	$(CC) -o casillero.o -c src/mapa/casilleros/casillero.cpp

CaminoMinimo.o: src/juego/grafo/CaminoMinimo.cpp
	$(CC) -o CaminoMinimo.o -c src/juego/grafo/CaminoMinimo.cpp

Dijkstra.o: src/juego/grafo/Dijkstra.cpp
	$(CC) -o Dijkstra.o -c src/juego/grafo/Dijkstra.cpp
	
Grafo.o: src/juego/grafo/Grafo.cpp
	$(CC) -o Grafo.o -c src/juego/grafo/Grafo.cpp

Vertice.o: src/juego/grafo/Vertice.cpp
	$(CC) -o Vertice.o -c src/juego/grafo/Vertice.cpp

valgrind:
	valgrind --tool=memcheck --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./andypolis

run: 
	./andypolis
