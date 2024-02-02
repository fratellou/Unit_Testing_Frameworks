CFLAGS=-Wall -Wextra -Werror
TEST=-lgtest -lgmock -pthread
EXIT=./objects/

all:calculator testing

calculator: calculator.o
	g++ $(CFLAGS) $(EXIT)calculator.o -o calculator

testing: 
	g++ ./tests/testing.cpp -o ./tests/testing $(TEST)

calculator.o:
	g++ $(CFLAGS) -c calculator.cpp -o $(EXIT)calculator.o

clean: 
	rm -rf $(EXIT)*.o calculator ./tests/testing

rebuild:clean all