#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "calc.hpp"

TEST(Calc, addTwoNumbers) {
  std::string input {"3 +5"};
  EXPECT_EQ(Calc::eval(input), 8);
}

//Copied from calculator test cases
TEST(CalculatorEvalTest, divideByZero) {
  std::string input {"(3+5) / ((8-3) * 0)"};
  EXPECT_THROW(Calc::eval(input), std::runtime_error);
}
TEST(InfixToPostfix, oneAdditionOneDivision) {
  std::vector<Calc::Token> infixVector = {{'n', 3}, {'+', 0}, {'n', 76}, {'/', 0}, {'n', 27}};
  std::vector<Calc::Token> postfixVector = {{'n', 3}, {'n', 76}, {'n', 27}, {'/', 0}, {'+', 0}};
  EXPECT_EQ(Calc::infixToPostfix(infixVector), postfixVector);
}

// write your own test cases to demonstrate the 
// added functionality

TEST(Calc, addTwoDoubles) {
  std::string input{"3.0 +5.2"};
  EXPECT_EQ(Calc::eval(input), 8.2);
}

TEST(Calc, powerOfTwo) {
  std::string input{"2^3^2"};
  EXPECT_EQ(Calc::eval(input), 512);
}

TEST(Calc, operatorPowerMult) {
  std::string input{"3^2+6*2"};
  EXPECT_EQ(Calc::eval(input), 21);
}

TEST(Calc, longerExpression) {
  std::string input{"4+5-(3+5)*15-3^2*2-5/3.5"};
  EXPECT_NEAR(Calc::eval(input), -130.428571, 0.000001);
}

TEST(Calc, multipleOperatorDouble) {
  std::string input{"7.5*3-3^3/2+62.7/3"};
  EXPECT_NEAR(Calc::eval(input), 29.9, 0.000001);
}

TEST(Calc, impliedMultBrackets) {
  std::string input{"(5+2)(4+2)"};
  EXPECT_EQ(Calc::eval(input), 42);
}

int main(int argc, char* argv[]) {
  // Input and print function for testing
  std::cin.clear();
  std::string input;
  std::cout << "Enter input: " << '\n';
  std::getline(std::cin, input);
  double result = Calc::eval(input);
  std::cout << result << '\n';

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
