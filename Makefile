CC = g++ -Wall -Werror -Wconversion
OBJS = main.o mapa.o materiales.o juego.o aserradero.o edificio.o escuela.o fabrica.o mina.o obelisco.o parser.o planta_electrica.o tipos_edificios.o casillero_construible.o casillero_inaccesible.o casillero_transitable.o casillero.o

andypolis: $(OBJS)
	$(CC) -o andypolis $(OBJS)
	rm -f *.o *~ 

main.o: main.cpp
	$(CC) -o main.o -c main.cpp

mapa.o: mapa.cpp
	$(CC) -o mapa.o -c mapa.cpp

materiales.o: materiales.cpp
	$(CC) -o materiales.o -c materiales.cpp

juego.o: juego.cpp
	$(CC) -o juego.o -c juego.cpp

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

planta_electrica.o: edificios/planta_electrica.cpp
	$(CC) -o planta_electrica.o -c edificios/planta_electrica.cpp

tipos_edificios.o: edificios/tipos_edificios.cpp
	$(CC) -o tipos_edificios.o -c edificios/tipos_edificios.cpp

casillero_construible.o: casilleros/casillero_construible.cpp
	$(CC) -o casillero_construible.o -c casilleros/casillero_construible.cpp

casillero_inaccesible.o: casilleros/casillero_inaccesible.cpp
	$(CC) -o casillero_inaccesible.o -c casilleros/casillero_inaccesible.cpp

casillero_transitable.o: casilleros/casillero_transitable.cpp
	$(CC) -o casillero_transitable.o -c casilleros/casillero_transitable.cpp

casillero.o: casilleros/casillero.cpp
	$(CC) -o casillero.o -c casilleros/casillero.cpp

valgrind:
	valgrind --tool=memcheck --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./andypolis

run: 
	./andypolis
