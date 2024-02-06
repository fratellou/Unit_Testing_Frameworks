#include <gtest/gtest.h>

#include "../calculator.h"

// ---------------------------------------------------------------

// Test PushCommand with a value 42
TEST(PushCommandTest, value42) {
  PushCommand pushCommand(42);
  ExecutionContext context;

  pushCommand.execute(context);

  ASSERT_EQ(context.operandStack.size(), 1);
  ASSERT_EQ(context.operandStack.top(), 42);
}

// Test PushCommand with a value -1
TEST(PushCommandTest, value_1) {
  PushCommand pushCommand(-1);
  ExecutionContext context;

  pushCommand.execute(context);
  ASSERT_EQ(context.operandStack.top(), -1);
}

// Test PushCommand with a value 10.5
TEST(PushCommandTest, value10_dot_5) {
  PushCommand pushCommand(10.5);
  ExecutionContext context;

  pushCommand.execute(context);
  ASSERT_EQ(context.operandStack.top(), 10.5);
}

// Test PushCommand with a parameter
TEST(PushCommandTest, valueParameter) {
  ExecutionContext context;
  DefineCommand defineCommand_a("a", 5);
  defineCommand_a.execute(context);
  PushCommand pushCommand(context.definedParameters["a"]);

  pushCommand.execute(context);
  ASSERT_EQ(context.operandStack.top(), 5);
}

// ---------------------------------------------------------------

// Test PopCommand
TEST(PopCommandTest, valueEmpty) {
  PopCommand popCommand;
  ExecutionContext context;

  // Attempting to pop from an empty stack should throw an exception
  ASSERT_THROW(popCommand.execute(context), std::runtime_error);
}

// Test PopCommand with a value 10.5
TEST(PopCommandTest, value10_dot_5) {
  PopCommand popCommand;
  ExecutionContext context;
  context.operandStack.push(10.5);
  context.operandStack.push(-1);

  popCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 10.5);
}

// Test PopCommand with a parameter
TEST(PopCommandTest, valueParameter) {
  PopCommand popCommand;
  ExecutionContext context;
  context.definedParameters["x"] = 10.0;
  context.definedParameters["y"] = 5;
  context.operandStack.push(context.definedParameters["x"]);
  context.operandStack.push(context.definedParameters["y"]);

  popCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 10.0);
}

// ---------------------------------------------------------------

// Test DefineCommand with a value 10.0
TEST(DefineCommandTest, value10_dot_0) {
  DefineCommand defineCommand("x", 10.0);
  ExecutionContext context;

  defineCommand.execute(context);

  ASSERT_EQ(context.definedParameters.size(), 1);
  ASSERT_EQ(context.definedParameters["x"], 10.0);
}

// ---------------------------------------------------------------

// Test SqrtCommand with a value 4
TEST(SqrtCommandTest, value4) {
  SqrtCommand sqrtCommand;
  ExecutionContext context;
  context.operandStack.push(4);

  sqrtCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 2);
}

// Test SqrtCommand with a value -4
TEST(SqrtCommandTest, value_4) {
  SqrtCommand sqrtCommand;
  ExecutionContext context;
  context.operandStack.push(-4);

  ASSERT_THROW(sqrtCommand.execute(context), std::runtime_error);
}

// Test SqrtCommand with an empty value
TEST(SqrtCommandTest, EmptySqrt) {
  SqrtCommand sqrtCommand;
  ExecutionContext context;
  ASSERT_THROW(sqrtCommand.execute(context), std::runtime_error);
}

// Test SqrtCommand with a parameter
TEST(SqrtCommandTest, valueParameter) {
  SqrtCommand sqrtCommand;
  ExecutionContext context;
  context.definedParameters["x"] = 25.0;
  context.operandStack.push(context.definedParameters["x"]);

  sqrtCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 5);
}

// ---------------------------------------------------------------

// Test AddCommand with values 2 and 5
TEST(AddCommandTest, value2_and_5) {
  AddCommand addCommand;
  ExecutionContext context;
  context.operandStack.push(2);
  context.operandStack.push(5);

  addCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 7);
}

// Test AddCommand with an empty value
TEST(AddCommandTest, valueEmpty) {
  AddCommand addCommand;
  ExecutionContext context;
  // Attempting to add from an empty stack should throw an exception
  ASSERT_THROW(addCommand.execute(context), std::runtime_error);
}

// Test AddCommand with parameter values
TEST(AddCommandTest, valueParameter) {
  AddCommand addCommand;
  ExecutionContext context;
  context.definedParameters["x"] = -10.0;
  context.definedParameters["y"] = 5;
  context.operandStack.push(context.definedParameters["x"]);
  context.operandStack.push(context.definedParameters["y"]);

  addCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), -5);
}

// ---------------------------------------------------------------

// Test SubCommand with values 2 and 5
TEST(SubCommandTest, value2_and_5) {
  SubCommand subCommand;
  ExecutionContext context;
  context.operandStack.push(2);
  context.operandStack.push(5);

  subCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), -3);
}

// Test SubCommand with an empty value
TEST(SubCommandTest, valueEmpty) {
  SubCommand subCommand;
  ExecutionContext context;
  // Attempting to substract from an empty stack should throw an exception
  ASSERT_THROW(subCommand.execute(context), std::runtime_error);
}

// Test SubCommand with parameter values
TEST(SubCommandTest, valueParameter) {
  SubCommand subCommand;
  ExecutionContext context;
  context.definedParameters["x"] = -10.0;
  context.definedParameters["y"] = 5;
  context.operandStack.push(context.definedParameters["x"]);
  context.operandStack.push(context.definedParameters["y"]);

  subCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), -15);
}

// ---------------------------------------------------------------

// Test MulCommand with values 2 and -5
TEST(MulCommandTest, value2_and__5) {
  MulCommand mulCommand;
  ExecutionContext context;
  context.operandStack.push(2);
  context.operandStack.push(-5);

  mulCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), -10);
}

// Test MulCommand with an empty value
TEST(MulCommandTest, valueEmpty) {
  MulCommand mulCommand;
  ExecutionContext context;
  // Attempting to multiply from an empty stack should throw an exception
  ASSERT_THROW(mulCommand.execute(context), std::runtime_error);
}

// Test MulCommand with parameter values
TEST(MulCommandTest, valueParameter) {
  MulCommand mulCommand;
  ExecutionContext context;
  context.definedParameters["x"] = -10.0;
  context.definedParameters["y"] = 0;
  context.operandStack.push(context.definedParameters["x"]);
  context.operandStack.push(context.definedParameters["y"]);

  mulCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 0);
}

// ---------------------------------------------------------------

// Test DivCommand with values 10 and 5
TEST(DivCommandTest, value10_and_5) {
  DivCommand divCommand;
  ExecutionContext context;
  context.operandStack.push(10);
  context.operandStack.push(5);

  divCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), 2);
}

// Test DivCommand with an empty value
TEST(DivCommandTest, valueEmpty) {
  DivCommand divCommand;
  ExecutionContext context;
  // Attempting to divide from an empty stack should throw an exception
  ASSERT_THROW(divCommand.execute(context), std::runtime_error);
}

// Test DivCommand with parameter values
TEST(DivCommandTest, valueParameter) {
  DivCommand divCommand;
  ExecutionContext context;
  context.definedParameters["x"] = -25.0;
  context.definedParameters["y"] = 5;
  context.operandStack.push(context.definedParameters["x"]);
  context.operandStack.push(context.definedParameters["y"]);

  divCommand.execute(context);

  ASSERT_EQ(context.operandStack.top(), -5);
}

// Test DivCommand with 0
TEST(DivCommandTest, value0) {
  DivCommand divCommand;
  ExecutionContext context;
  context.operandStack.push(1);
  context.operandStack.push(0);

  // Attempting to divide by 0 should throw an exception
  ASSERT_THROW(divCommand.execute(context), std::runtime_error);
}

// ---------------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
