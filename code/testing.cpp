#include <gtest/gtest.h>

TEST(CalculatorTest, PushCommand) {
    ExecutionContext context;
    CommandFactory factory;
    std::vector<std::string> args = { "5.0" };
    auto pushCommand = factory.createCommand("PUSH", args);
    pushCommand->execute(context);

    ASSERT_EQ(context.operandStack.size(), 1);
    ASSERT_EQ(context.operandStack.top(), 5.0);
}

TEST(CalculatorTest, PopCommand) {
    ExecutionContext context;
    CommandFactory factory;
    context.operandStack.push(7.0);
    auto popCommand = factory.createCommand("POP", {});
    popCommand->execute(context);

    ASSERT_TRUE(context.operandStack.empty());
}

// Добавьте другие тесты для остальных команд и функциональности калькулятора

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
