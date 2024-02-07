## Unit_testing_frameworks

1. Write a stack calculator that takes as a command-line argument the name of the file containing the commands. Implement a set of unit tests covering the functionality of the calculator. 
2. Implement a set of unit tests covering the functionality https://github.com/fratellou/NoSQL-database using on Google Test. 

## Contents

1. [Task 1](#task-1) \
    1.1 [Task 1. Information](#task-1-information) \
    1.2 [Task 1. Code](#task-1-code)
2. [Task 2](#task-2) \
    2.1 [Task 2. Information](#task-2-information) \
    2.2 [Task 2. Code](#task-2-code)

# Task 1

Write a stack calculator that takes as a command-line argument the name of the file containing the commands. If there is no argument, then use the standard input stream to read commands. Use real numbers.  
Implement a set of unit tests covering the functionality of the calculator. 
The program implements the following set of commands: 
- \# is a line with a comment. 
- POP, PUSH — remove/put the number from / on the stack(a). 
- \+ , - , * , /, SQRT – arithmetic operations. Use one or two top elements of the stack, remove them from the stack, placing the result back PRINT — printing the top element of the stack (without deleting). 
- DEFINE — set the value of the parameter. In the future, use this value instead of the parameter everywhere.  
 
Example (should output 2):
> DEFINE a 4 
>
> PUSH a SQRT  
>
> PRINT  
>

Methodological guidelines: 
It is recommended to implement the creation of commands using the "factory method" design pattern. 
Arguments to the command (those who have arguments) can be passed for execution in the form of a list of objects, the command itself must be able to interpret its arguments 
The contents of the stack and a list (preferably an associative container std::map<std::string, double>) of certain named parameters should be passed to the command as a special execution context object  
Develop a hierarchy of exceptions that will throw commands when executed. In case of an exception, output error information and continue executing the program (from a file or commands entered from the console). 
To implement unit tests, use the Google Test Framework

## Task 1. Information

A detailed explanation of the factory method can be found in the repository https://github.com/fratellou/Factory_method .

Installing Google Test Framework on Ubuntu:

> sudo apt-get install libgtest-dev libgmock-dev # for ubuntu 20
>
> sudo apt-get install google-mock # for ubuntu 18

After installing them, the gtest and gmock folders will appear in the directory with the header files /usr/include/. However, for the framework to work properly, it also needs multithreading support. Let's add it:

> sudo apt-get install libtbb-dev

To compile, you will need to install the cmake package:

> sudo apt-get install cmake

When you installed libgtest-dev a little higher, the googletest and googlemock sources were also added to your system, which can be found in the /usr/src/googletest/ directory.

Let's go there:

> cd /usr/src/googletest/

Create a directory for the assembly and go to it:

> sudo mkdir build
>

> cd build
>

In this directory, run the command:

> sudo cmake ..

Two dots next to cmake mean that you need to search for the script file CMakeLists.txt in the parent directory. This command will generate a set of instructions for compiling and building the gtest and gmock libraries. After that, it remains to execute:

> sudo make

If everything goes well, a new lib directory will be created, where 4 files will be located:

`libgmock.a, libgmock_main.a, libgtest.a, libgtest_main.a`

These files contain the implementation of the framework's functionality and they need to be copied to the directory of the other libraries.:

> sudo cp lib/* /usr/lib

*For ubuntu 18, the libraries will be located in ./googlemock/ and ./googlemock/gtest/
After copying, the build directory can be deleted.

After that, you can go to the directory with the project and run the Makefile.

To run unit tests, go to the test directory and run the bash script:

> sh tester.sh

## Task 1. Code

The `ExecutionContext` class contains the state of the calculator: 
- `operandStack` - stack for storing operands;
- `definedParameters` display for storing user parameters.

The `Command` class is an abstract base class representing a calculator command. It declares a purely virtual function `execute()`, which the derived classes must implement. The destructor is declared virtual in order to properly release resources.

The `PushCommand' class represents a command to add a value to the operand stack. Takes a value as a parameter and implements the `execute()` function to add a value to the operand stack.

The `PopCommand` class represents a command to extract a value from the operand stack. Implements the `execute()` function to check for the presence of elements in the stack and extract the top value.

The `PrintCommand` class represents a command to output the top value of the operand stack. Implements the `execute()` function to check for the presence of elements in the stack and output the upper value.

The `DefineCommand` class represents a command to define a parameter with a given value. Accepts the parameter name and its value, implements the `execute()` function to add the parameter to the 'definedParameters` display.

The `SqrtCommand` class represents a command to calculate the square root from the top value of the operand stack. Checks for the presence of elements in the stack and the negativity of the operand, implements the `execute()` function to perform the square root extraction operation.

The `addCommand` class represents a command for adding the top two values of the operand stack. Checks for an insufficient number of operands, implements the `execute()` function to perform addition.

The `SubCommand` class represents a command to subtract the top two values of the operand stack. Checks for an insufficient number of operands, implements the `execute()` function to perform subtraction.

The `MulCommand` class represents a command for multiplying the top two values of the operand stack. Checks for an insufficient number of operands, implements the `execute()` function to perform multiplication.

The `DivCommand` class represents a command to divide the top two values of the operand stack. Checks for an insufficient number of operands and division by zero, implements the `execute()` function to perform division.

The `NumCommand` class provides a command to skip a line starting with '#'. It does not do anything, it serves as a placeholder for comments.

The `CommandFactory` class is an abstract base class that represents a factory for creating command instances. It declares a purely virtual function `createCommand()`, which the derived classes must implement.

The `PushCommandFactory` class is a specific factory for creating instances of `PushCommand`.

The `PopCommandFactory` class is a specific factory for creating instances of `PopCommand`.

The `PrintCommandFactory` class is a specific factory for creating instances of `PrintCommand`.

The `DefineCommandFactory` class is a specific factory for creating instances of `DefineCommand`.

The `SqrtCommandFactory` class is a specific factory for creating instances of `SqrtCommand`.

The `AddCommandFactory` class is a specific factory for creating instances of `addCommand`.

The `SubCommandFactory` class is a specific factory for creating instances of `SubCommand`.

The `MulCommandFactory` class is a specific factory for creating instances of `MulCommand`.

The `DivCommandFactory` class is a specific factory for creating instances of `DivCommand`.

The 'NumCommandFactory` class is a specific factory for creating instances of `NumCommand`.

The `Factory` class provides a static `createCommand()` method that uses the corresponding factory based on the command name, returning an instance of the corresponding command.

`main()` is the main function of the program. Checks the number of command line arguments: 
- if one argument is passed, the `executeCommandsFromFile()` function is called to execute commands from the file; 
- if there are no arguments, `executeCommandsFromStdin()` is called to execute commands from standard input.

`executeCommandsFromFile()` - the function executes commands by reading them from a file with the specified name. If the file cannot be opened, an error message is displayed.

`executeCommandsFromStdin()` - the function executes commands by reading them from the standard input. The input continues until the "exit" command is entered.

`processCommand()` - the function processes the command string. It splits the string into tokens, creates an instance of the command using the factory, and executes this command with the global `ExecutionContext'. If an exception occurs, an error message is output to the standard error stream (cerr).

# Task 2

1. Implement classes with a basic set of operations (private, public):
- array;
- list (single-linked, double-linked);
- queue;
- stack;
- hash table;
- binary tree.
2. Implement the Stack class with a basic set of operations (private, public).
3. Implement Google test coverage (at least 90%).

## Task 2. Information

The full explanation of the structures is in the repository https://github.com/fratellou/NoSQL-database.

## Task 2. Code

Array class:

`add()`- adds an element to the end of the array.

`insert()` - inserts an element into the specified array index.

`removeLast()` - removes the last element from the array.

`removeAtIndex()` - removes an element at the specified index from the array.

`get()` - gets the value at the specified index in the array.

`change()` - changes the value at the specified index in the array.

`search()` - searches for an element in the array and returns its index.

Double Linked List Class:

`addToBeginning()` - adds an item to the top of the list.

`addToEnd()` - adds an item to the end of the list.

`removeByValue()` - removes the first occurrence of the specified value from the list.

`removeFromEnd()` - removes the last item from the list.

`insertAtIndex()` - inserts an element at the specified index in the list.

`removeFromBeginning()` - removes the first item from the list.

`removeAtIndex()` - removes an item at the specified index from the list.

`search()` - searches for a value in the list and returns its index.

Hash Table class:

`set()` - inserts or updates a key-value pair into a hash table.

`del()` - removes the key-value pair from the hash table.

`get()` - returns the value associated with the specified key in the hash table.

Linked List Class:

`add()` - adds an item to the top of the list.

`insert()` - inserts an element at the specified index in the list.

`remove()` - removes the first item from the list.

`removeByIndex()` - removes an item at the specified index from the list.

`removeByValue()` - removes the first occurrence of the specified value from the list.

`search()` - searches for a value in the list and returns its index.

`print()` - displays the list items on the screen.


Queue class:

`push()` - adds an item to the end of the queue.

`pop()` - deletes and returns the first item from the queue.

Stack Class:

`push()` - adds an element to the top of the stack.

`pop()` - removes and returns an element from the top of the stack.

The Tree class:

`add()` - adds a node with the specified key to the tree.

`search()` - searches for a node with the specified key in the tree.

`succ()` - returns the successor of the node in the tree.

`min()` - returns the node with the minimum key in the tree.

`del()` - removes the node with the specified key from the tree.

`transplant()` - replaces one subtree with another in the tree.

`print()` - displays the contents of the tree on the screen in a structured format.

>
> fratellou, 2024
