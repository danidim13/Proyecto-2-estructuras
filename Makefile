CC = g++ -Wall -std=c++11 
inc = ./include
src := $(wildcard source/*.cpp)
obj := $(notdir $(src:.cpp=.o))

%.o: source/%.cpp
	$(CC) -I $(inc) ${MACROS} -c -o $@ $<

all: $(obj) 

tests: all main.cpp
	$(CC) -I $(inc) $(obj) main.cpp


clean:
	rm -f *.o *.out
