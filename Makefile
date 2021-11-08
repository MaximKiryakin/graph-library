all: solution.o graph_lib.o
	gcc solution.o graph_lib.o -o solution


graph_lib.o: graph_lib.c graph_lib.h
	gcc graph_lib.c -c

solution.o: solution.c graph_lib.h
	gcc solution.c -c 

graph_lib_test.o: graph_lib_test.c graph_lib.h
	gcc graph_lib_test.c -c

test: graph_lib_test.o graph_lib.o
	gcc graph_lib_test.o graph_lib.o -o test

clean:
	rm -f graph_lib.o solution.o graph_lib_test.o