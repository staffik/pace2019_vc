CPPFLAGS= -g

objects = vc.o io.o graph.o hopcroft_carp.o #kernel_2k.o

#main: $(objects)
solve: $(objects)

graph.o: graph.h graph.cpp

vc.o: vc.h vc.cpp graph.o

io.o: io.h io.cpp

hopcroft_carp.o: hopcroft_carp.h hopcroft_carp.cpp graph.o

#kernel_2k.o: kernel_2k.h kernel_2k.cpp graph.o hopcroft_carp.o

clean:
	rm -f $(objects) main solve
