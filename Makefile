CC = g++ -Wall -std=c++11 
inc = ./include
src := $(wildcard source/*.cpp)
obj := $(notdir $(src:.cpp=.o))

%.o: source/%.cpp
	$(CC) -I $(inc) ${MACROS} -c -o $@ $<

all: $(obj) 

Prueba1: pruebas/prueba_iteraciones.cpp $(obj)
	$(CC) -I $(inc) $^ -o pruebas/Prueba1.out

tests: all main.cpp
	$(CC) -I $(inc) $(obj) main.cpp

run: Prueba1
	@echo "Corriendo Prueba1 ..."
	@./pruebas/Prueba1.out 100
	@echo "FIN"
	@mv prueba_*.txt Resultados

clean:
	rm -f *.o *.out pruebas/*.out Resultados/*.txt
