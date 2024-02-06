#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;
void executeCommandsFromFile(const string& filename);
void executeCommandsFromStdin();
void processCommand(const string& command);

// ExecutionContext class holds the state of the calculator
class ExecutionContext {
 public:
  stack<double> operandStack;             // Stack to hold operands
  map<string, double> definedParameters;  // Map to store defined parameters
};

ExecutionContext executionContext;  // Global instance of ExecutionContext

// Command is an abstract class representing a calculator command
class Command {
 public:
  virtual void execute(ExecutionContext& context) const = 0;
  virtual ~Command() = default;
};

// PushCommand pushes a value onto the operand stack
class PushCommand : public Command {
 public:
  explicit PushCommand(double val) : value(val) {}

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
      throw runtime_error(
          "Pop from an empty stack.");  // Error if stack is empty
    }
    context.operandStack.pop();  // Pop the top value from the stack
  }
};

// PrintCommand prints the top value on the operand stack
class PrintCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.empty()) {
      throw runtime_error(
          "Print from an empty stack.");  // Error if stack is empty
    }
    cout << context.operandStack.top() << endl;  // Print the top value
  }
};

// DefineCommand defines a parameter with a specified value
class DefineCommand : public Command {
 private:
  string paramName;
  double paramValue;

 public:
  DefineCommand(const string& name, double value)
      : paramName(name), paramValue(value) {}

  void execute(ExecutionContext& context) const override {
    context.definedParameters[paramName] =
        paramValue;  // Define the parameter in the ExecutionContext
  }
};

// SqrtCommand calculates the square root of the top value on the operand stack
class SqrtCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.empty()) {
      throw runtime_error(
          "SQRT from an empty stack.");  // Error if stack is empty
    }
    double operand = context.operandStack.top();
    if (operand < 0) {
      throw runtime_error(
          "The number under the SQRT must not be negative");  //  SQRT of a
                                                              //  negative
                                                              //  number
    }
    context.operandStack.pop();
    context.operandStack.push(
        sqrt(operand));  // Push the square root back onto the stack
  }
};

// AddCommand adds the top two values on the operand stack
class AddCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.size() < 2) {
      throw runtime_error(
          "Insufficient operands for addition.");  // Error if there are not
                                                   // enough operands
    }
    double operand2 = context.operandStack.top();
    context.operandStack.pop();
    double operand1 = context.operandStack.top();
    context.operandStack.pop();
    context.operandStack.push(operand1 +
                              operand2);  // Push the result back onto the stack
  }
};

// SubCommand substracts the top two values on the operand stack
class SubCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.size() < 2) {
      throw runtime_error(
          "Insufficient operands for subtraction.");  // Error if there are not
                                                      // enough operands
    }
    double operand2 = context.operandStack.top();
    context.operandStack.pop();
    double operand1 = context.operandStack.top();
    context.operandStack.pop();
    context.operandStack.push(operand1 -
                              operand2);  // Push the result back onto the stack
  }
};

// MulCommand multiplies the top two values on the operand stack
class MulCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.size() < 2) {
      throw runtime_error(
          "Insufficient operands for multiplication.");  // Error if there are
                                                         // not enough operands
    }
    double operand2 = context.operandStack.top();
    context.operandStack.pop();
    double operand1 = context.operandStack.top();
    context.operandStack.pop();
    context.operandStack.push(operand1 *
                              operand2);  // Push the result back onto the stack
  }
};

// DivCommand divides the top two values on the operand stack
class DivCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    if (context.operandStack.size() < 2) {
      throw runtime_error(
          "Insufficient operands for division.");  // Error if there are not
                                                   // enough operands
    }
    double operand2 = context.operandStack.top();
    context.operandStack.pop();
    double operand1 = context.operandStack.top();
    context.operandStack.pop();
    if (operand2 == 0) {
      throw runtime_error(
          "An attempt to divide by 0.");  // Error when dividing by 0
    }
    context.operandStack.push(operand1 /
                              operand2);  // Push the result back onto the stack
  }
};

// CommentCommand skips a line starting with '#'
class NumCommand : public Command {
 public:
  void execute(ExecutionContext& context) const override {
    (void)context;  // Suppress unused parameter warning
    // This command does nothing, as it is just meant to skip comments
  }
};

// Abstract Factory class
class CommandFactory {
 public:
  virtual unique_ptr<Command> createCommand(
      const vector<string>& args) const = 0;
  virtual ~CommandFactory() = default;
};

// Concrete factory for PushCommand
class PushCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    if (args.size() != 1) {
      throw invalid_argument("PUSH command requires one argument.");
    }
    if ((args[0][0] > 64 && args[0][0] < 91) ||
        (args[0][0] > 96 && args[0][0] < 123)) {
      return make_unique<PushCommand>(
          executionContext.definedParameters[args[0]]);
    }
    return make_unique<PushCommand>(
        stod(args[0]));  // Create PushCommand with the specified value
  }
};

// Concrete factory for PopCommand
class PopCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<PopCommand>();
  }
};

// Concrete factory for PrintCommand
class PrintCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<PrintCommand>();
  }
};

// Concrete factory for DefineCommand
class DefineCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    if (args.size() == 2) {
      return make_unique<DefineCommand>(args[0], stod(args[1]));
    } else if (args.size() == 1) {
      return make_unique<DefineCommand>(args[0], 0.0);
    } else {
      throw invalid_argument("DEFINE command requires one or two arguments.");
    }
  }
};

// Concrete factory for SqrtCommand
class SqrtCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<SqrtCommand>();
  }
};

// Concrete factory for AddCommand
class AddCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<AddCommand>();
  }
};

// Concrete factory for SubCommand
class SubCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<SubCommand>();
  }
};

// Concrete factory for MulCommand
class MulCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<MulCommand>();
  }
};

// Concrete factory for DivCommand
class DivCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<DivCommand>();
  }
};

// Concrete factory for NumCommand
class NumCommandFactory : public CommandFactory {
 public:
  unique_ptr<Command> createCommand(const vector<string>& args) const override {
    (void)args;  // Suppress unused parameter warning
    return make_unique<NumCommand>();
  }
};

// Factory creates instances of specific commands based on the command name
class Factory {
 public:
  static unique_ptr<Command> createCommand(const string& commandName,
                                           const vector<string>& args) {
    // Use the appropriate factory based on commandName
    if (commandName == "PUSH") {
      PushCommandFactory factory;
      return factory.createCommand(
          args);  // Create PushCommand with the specified value
    } else if (commandName == "POP") {
      PopCommandFactory factory;
      return factory.createCommand(args);  // Create PopCommand
    } else if (commandName == "PRINT") {
      PrintCommandFactory factory;
      return factory.createCommand(args);  // Create PrintCommand
    } else if (commandName == "DEFINE") {
      DefineCommandFactory factory;
      return factory.createCommand(args);
    } else if (commandName == "SQRT") {
      SqrtCommandFactory factory;
      return factory.createCommand(args);  // Create SqrtCommand
    } else if (commandName == "+") {
      AddCommandFactory factory;
      return factory.createCommand(args);  // Create AddCommand
    } else if (commandName == "-") {
      SubCommandFactory factory;
      return factory.createCommand(args);  // Create SubCommand
    } else if (commandName == "*") {
      MulCommandFactory factory;
      return factory.createCommand(args);  // Create MulCommand
    } else if (commandName == "/") {
      DivCommandFactory factory;
      return factory.createCommand(args);  // Create DivCommand
    } else if (commandName == "#") {
      NumCommandFactory factory;
      return factory.createCommand(args);  // Create NumCommand
    } else {
      throw invalid_argument("Unknown command.");  // Error for unknown command
    }
  }
};

#endif