CFLAGS=-Wall -Wextra -Werror
TEST=-lgtest -lgmock -pthread
EXIT=./objects/

all:calculator testing struct_testing

calculator: calculator.o
	g++ $(CFLAGS) $(EXIT)calculator.o -o calculator

testing: 
	g++ ./tests/testing.cpp -o ./tests/testing $(TEST)

struct_testing:
	g++ ./tests/struct_testing.cpp -o ./tests/struct_testing $(TEST)

calculator.o:
	g++ $(CFLAGS) -c calculator.cpp -o $(EXIT)calculator.o

clean: 
	rm -rf $(EXIT)*.o calculator ./tests/testing ./tests/struct_testing

rebuild:clean all