CC = g++ -Wall -Werror -Wconversion
OBJS = main.o mapa.o utilesMenu.o materiales.o jugador.o juego.o aserradero.o edificio.o escuela.o fabrica.o mina.o obelisco.o parser.o plantaElectrica.o tiposEdificios.o casilleroConstruible.o casilleroInaccesible.o casilleroTransitable.o casillero.o

andypolis: $(OBJS)
	$(CC) -o andypolis $(OBJS)
	rm -f *.o *~ 

main.o: main.cpp
	$(CC) -o main.o -c main.cpp

mapa.o: mapa.cpp
	$(CC) -o mapa.o -c mapa.cpp

utilesMenu.o: utilesMenu.cpp
	$(CC) -o utilesMenu.o -c utilesMenu.cpp

materiales.o: materiales.cpp
	$(CC) -o materiales.o -c materiales.cpp

juego.o: juego.cpp
	$(CC) -o juego.o -c juego.cpp

jugador.o: jugadores/jugador.cpp
	$(CC) -o jugador.o -c jugadores/jugador.cpp	

aserradero.o: edificios/aserradero.cpp
	$(CC) -o aserradero.o -c edificios/aserradero.cpp

edificio.o: edificios/edificio.cpp
	$(CC) -o edificio.o -c edificios/edificio.cpp

escuela.o: edificios/escuela.cpp
	$(CC) -o escuela.o -c edificios/escuela.cpp

fabrica.o: edificios/fabrica.cpp
	$(CC) -o fabrica.o -c edificios/fabrica.cpp

mina.o: edificios/mina.cpp
	$(CC) -o mina.o -c edificios/mina.cpp

obelisco.o: edificios/obelisco.cpp
	$(CC) -o obelisco.o -c edificios/obelisco.cpp

parser.o: edificios/parser.cpp
	$(CC) -o parser.o -c edificios/parser.cpp

plantaElectrica.o: edificios/plantaElectrica.cpp
	$(CC) -o plantaElectrica.o -c edificios/plantaElectrica.cpp

tiposEdificios.o: edificios/tiposEdificios.cpp
	$(CC) -o tiposEdificios.o -c edificios/tiposEdificios.cpp

casilleroConstruible.o: casilleros/casilleroConstruible.cpp
	$(CC) -o casilleroConstruible.o -c casilleros/casilleroConstruible.cpp

casilleroInaccesible.o: casilleros/casilleroInaccesible.cpp
	$(CC) -o casilleroInaccesible.o -c casilleros/casilleroInaccesible.cpp

casilleroTransitable.o: casilleros/casilleroTransitable.cpp
	$(CC) -o casilleroTransitable.o -c casilleros/casilleroTransitable.cpp

casillero.o: casilleros/casillero.cpp
	$(CC) -o casillero.o -c casilleros/casillero.cpp

valgrind:
	valgrind --tool=memcheck --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./andypolis

run: 
	./andypolis
