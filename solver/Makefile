CPPFLAGS= -o3

objects = vc.o io.o graph.o hopcroft_carp.o kernel_2k.o solve.o folding.o

main: $(objects)

graph.o: graph.h graph.cpp

vc.o: vc.h vc.cpp graph.o

io.o: io.h io.cpp

folding.o: folding.h folding.cpp graph.o vc.o solve.o

hopcroft_carp.o: hopcroft_carp.h hopcroft_carp.cpp graph.o

kernel_2k.o: kernel_2k.h kernel_2k.cpp graph.o hopcroft_carp.o

solve.o: solve.h solve.cpp graph.o vc.o kernel_2k.o

clean:
	rm -f $(objects) main
