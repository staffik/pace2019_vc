objects = vc.o lp.o io.o graph.o

main: $(objects)

graph.o: graph.h graph.cpp

vc.o: vc.h vc.cpp graph.o

lp.o: lp.h lp.cpp vc.o

io.o: io.h io.cpp

clean:
	rm -f $(objects) main
