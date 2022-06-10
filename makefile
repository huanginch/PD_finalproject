main.exe: main.o fileIO.o inventoryOperation.o orderOperation.o sort.o
	gcc -o main.exe main.o fileIO.o inventoryOperation.o orderOperation.o sort.o
	 
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