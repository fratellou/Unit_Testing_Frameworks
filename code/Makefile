CFLAGS=-Wall -Wextra -Werror
EXIT=./objects/

all:calculator

calculator: calculator.o
	g++ $(CFLAGS) $(EXIT)calculator.o -o calculator

testing: testing.o
	g++ $(CFLAGS) $(EXIT)testing.o -o testing

calculator.o:
	g++ $(CFLAGS) -c calculator.cpp -o $(EXIT)calculator.o

testing.o:
	g++ $(CFLAGS) -c testing.cpp -o $(EXIT)testing.o

clean: 
	rm -rf $(EXIT)*.o calculator testing

rebuild:clean all