output: src/*.o
	gcc -Wall src/*.o -o executable/stack-simulator

main.o: src/main.c src/main.h
	gcc -c src/main.c

globals.o: src/globals.c src/globals.h
	gcc -c src/globals.c

filehandler.o: src/filehandler.c src/filehandler.h
	gcc -c src/filehandler.c

instructions.o: src/instructions.c src/instructions.h
	gcc -c src/instructions.c

initialize.o: src/initialize.c src/initialize.h
	gcc -c src/initialize.c

fixedpoint.o: src/fixedpoint.c src/fixedpoint.h
	gcc -c src/fixedpoint.c

debug.c: src/debug.c src/debug.h
	gcc -c src/debug.c

clean:
	rm src/*.o stack-simulator