main.exe: main.o fileIO.o inventoryOperation.o orderOperation.o sort.o
	gcc -o main.exe main.o fileIO.o inventoryOperation.o orderOperation.o sort.o
	 
main.o: main.c basic.h orderOperation.h inventoryOperation.h sort.h fileIO.h
	gcc -c main.c
	 
fileIO.o: fileIO.c fileIO.h
	gcc -c fileIO.c
	 
inventoryOperation.o: inventoryOperation.c inventoryOperation.h basic.h myDS.h
	gcc -c inventoryOperation.c

orderOperation.o: orderOperation.c orderOperation.h basic.h myDS.h
	gcc -c orderOperation.c

sort.o: sort.c orderOperation.h basic.h myDS.h
	gcc -c sort.c

clean:
	rm -f *.o