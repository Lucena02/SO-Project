	


all: server client
server: bin/sdstored
client: bin/sdstore



bin/sdstored: obj/sdstored.o
	gcc -g obj/sdstored.o -o bin/sdstored


obj/sdstored.o: src/sdstored.c
	gcc -g -o obj/sdstored.o src/sdstored.c -c -W -Wall


bin/sdstore: obj/sdstore.o
	gcc -g obj/sdstore.o -o bin/sdstore


obj/sdstore.o: src/sdstore.c
	gcc -g -o obj/sdstore.o src/sdstore.c -c -W -Wall


clean:
	rm -f obj/* tmp/* bin/sdstored bin/sdstore *~


