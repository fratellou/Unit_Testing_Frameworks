#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream> 
#include <vector> 
#include <stack>
#include <map>
#include <cmath>
#include <stdexcept>
#include <iterator> 
#include <memory> 
#include <fstream> 
#include <sstream> 
using namespace std;

// ExecutionContext class holds the state of the calculator
class ExecutionContext {
public:
    stack<double> operandStack;          // Stack to hold operands
    map<string, double> definedParameters;  // Map to store defined parameters
};

ExecutionContext executionContext;  // Global instance of ExecutionContext

// Command is an abstract class representing a calculator command
class Command {
public:
    virtual void execute(ExecutionContext& context) const = 0;  // Execute the command
    virtual ~Command() = default; 
};

// pushes a value onto the operand stack
class PushCommand : public Command {
public:
    explicit PushCommand(double val) : value(val) {}  // Constructor with initialization

    void execute(ExecutionContext& context) const override {
        context.operandStack.push(value);  // Push the value onto the stack
    }
private:
    double value;  // Value to be pushed onto the stack
};

// PopCommand pops a value from the operand stack
class PopCommand : public Command {
public:
    void execute(ExecutionContext& context) const override {
        if (context.operandStack.empty()) {
            throw std::runtime_error("Error: Pop from an empty stack.");  // Error if stack is empty
        }
        context.operandStack.pop();  // Pop the top value from the stack
    }
};

// AddCommand adds the top two values on the operand stack
class AddCommand : public Command {
public:
    void execute(ExecutionContext& context) const override {
        if (context.operandStack.size() < 2) {
            throw std::runtime_error("Error: Insufficient operands for addition.");  // Error if there are not enough operands
        }
        double operand2 = context.operandStack.top();
        context.operandStack.pop();
        double operand1 = context.operandStack.top();
        context.operandStack.pop();
        context.operandStack.push(operand1 + operand2);  // Push the result back onto the stack
    }
};

// PrintCommand prints the top value on the operand stack
class PrintCommand : public Command {
public:
    void execute(ExecutionContext& context) const override {
        if (context.operandStack.empty()) {
            throw std::runtime_error("Error: Print from an empty stack.");  // Error if stack is empty
        }
        std::cout << context.operandStack.top() << std::endl;  // Print the top value
    }
};

// DefineCommand defines a parameter with a specified value
class DefineCommand : public Command {
private:
    std::string paramName;
    double paramValue;

public:
    DefineCommand(const std::string& name, double value) : paramName(name), paramValue(value) {}

    void execute(ExecutionContext& context) const override {
        context.definedParameters[paramName] = paramValue;  // Define the parameter in the ExecutionContext
    }
};

// CommandFactory creates instances of specific commands based on the command name
class CommandFactory {
public:
    static unique_ptr<Command> createCommand(const string& commandName, const vector<string>& args) {
        if (commandName == "PUSH") {
            if (args.size() != 1) {
                throw invalid_argument("PUSH command requires one argument.");  
            }
            cout << args[0];
            return make_unique<PushCommand>(stod(args[0]));  // Create PushCommand with the specified value
        }
        else if (commandName == "POP") {
            return std::make_unique<PopCommand>();  // Create PopCommand
        }
        else if (commandName == "ADD") {
            return std::make_unique<AddCommand>();  // Create AddCommand
        }
        else if (commandName == "PRINT") {
            return std::make_unique<PrintCommand>();  // Create PrintCommand
        }
        else if (commandName == "DEFINE") {
            if (args.size() == 2) {
                return make_unique<DefineCommand>(args[0], stod(args[1]));  // Create DefineCommand with name and value
            } else if (args.size() == 1) {
                return make_unique<DefineCommand>(args[0], 0.0);  // Default value if no second argument
            } else {
                throw invalid_argument("DEFINE command requires one or two arguments.");  // Error if incorrect number of arguments
            }
        }
        else {
            throw invalid_argument("Unknown command.");  // Error for unknown command
        }
    }
};

#endif