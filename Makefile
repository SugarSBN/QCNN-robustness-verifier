objects = src/circuit.o \
		src/complex.o \
		src/matrix.o \
		src/purestate.o \
		src/state.o \
		src/polygon.o \
		src/verifier.o \

main : $(objects) main.o
	g++ $(objects) main.o -o $@

main.o : main.cpp
	g++ main.cpp -c

predict : $(objects) predict.o
	g++ $(objects) predict.o -o $@

predict.o : predict.cpp
	g++ predict.cpp -c

/src/%.o : /src/%.cpp
	g++ $< -c

src/%.cpp : src/%.h

clean:
	rm *.o *.exe src\\*.o