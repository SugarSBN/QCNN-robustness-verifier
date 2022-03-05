objects = main.o \
		src/circuit.o \
		src/complex.o \
		src/matrix.o \
		src/simustate.o \

main : $(objects)
	g++ $(objects) -o $@

main.o : main.cpp
	g++ main.cpp -c

/src/%.o : /src/%.cpp
	g++ $< -c

src/%.cpp : src/%.h

clean:
	rm *.o *.exe src\\*.o