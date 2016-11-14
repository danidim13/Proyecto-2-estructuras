CC = g++ -Wall -std=c++11

inc = ./include
src := $(wildcard source/*.cpp)
obj := $(notdir $(src:.cpp=.o))

%.o: source/%.cpp
	$(CC) -I $(inc) -c -o $@ $<

all: $(obj)
	$(CC) -I $(inc) $(obj)

#tests: $(obj)


clean:
	rm -f *.o *.out
