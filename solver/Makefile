objects = vc.o lp.o io.o graph.o hopcroft_carp.o kernel_2k.o

main: $(objects)

graph.o: graph.h graph.cpp

vc.o: vc.h vc.cpp graph.o

lp.o: lp.h lp.cpp vc.o

io.o: io.h io.cpp

hopcroft_carp.o: hopcroft_carp.h hopcroft_carp.cpp graph.o

kernel_2k.o: kernel_2k.h kernel_2k.cpp graph.o

clean:
	rm -f $(objects) main
