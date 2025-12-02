#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "calc.hpp"

std::ostream& Calc::operator<<(std::ostream& out, const Calc::Token& t) {
  out << "{'" << t.type << "', " << t.val << '}';
  return out;
}

bool Calc::operator==(const Calc::Token& a, const Calc::Token& b) {
  if (a.type != b.type) {
    return false;
  }
  if (a.type == 'n') {
    return a.val == b.val;
  }
  return true;
}

// Function for precedence, (*/ over +-)
static int prec(char type) {
  auto prec = 0;
  if (type == '*' || type == '/') prec = 2;
  if (type == '+' || type == '-') prec = 1;
  return prec;
}

// This is the function for you to write
std::vector<Calc::Token> Calc::infixToPostfix(const std::vector<Token>& input) {
  std::vector<Token> output;
  std::vector<Token> operatorStack;
  // For each token in input
  for (Token t : input) {
    //If token is a number, add to output
    if (t.type == 'n') { 
      output.push_back(t);
      } else if (t.type =='(') {
        operatorStack.push_back(t);
      } else if (t.type == ')') {
        //Remove tokens from stack and push them back to output until '('
        while (!operatorStack.empty() && operatorStack.back().type != '(') {
          output.push_back(operatorStack.back());
          operatorStack.pop_back(); 
        }
        //  Remove '(' from stack
        operatorStack.pop_back();
      } else {
        // Precedence of t
        int tprec = prec(t.type);
        while (!operatorStack.empty() && operatorStack.back().type != '(') {
        // Precedence of operatorStack.back(), (end is top element)
        int sprec = prec(operatorStack.back().type);
         if (sprec >= tprec) {
          output.push_back(operatorStack.back());
          operatorStack.pop_back();
          } else {
            break;
          }
        }
        operatorStack.push_back(t);
      }
  }
  //Reverse stack and append to end of output
  output.insert(output.end(), operatorStack.rbegin(), operatorStack.rend());
  return output; 
}

// evalPostfix evaluates a vector of tokens in postfix notation
// This function was done in tutorial Week 10
int Calc::evalPostfix(const std::vector<Token>& tokens) {
  if (tokens.empty()) {
    return 0;
  }
  std::vector<int> stack;
  for (Token t : tokens) {
    if (t.type == 'n') {
      stack.push_back(t.val);
    } else {
      int val = 0;
      if (t.type == '+') {
        val = stack.back() + *(stack.end()-2);
      } else if (t.type == '*') {
        val = stack.back() * *(stack.end()-2);
      } else if (t.type == '-') {
        val = *(stack.end()-2) - stack.back();
      } else if (t.type == '/') {
        if (stack.back() == 0) {
          throw std::runtime_error("divide by zero");
        }
        val = *(stack.end()-2) / stack.back();
      } else {
          std::cout << "invalid token\n";
      }
      stack.pop_back();
      stack.pop_back();
      stack.push_back(val);
    }
  }
  return stack.back();
}

// tokenise takes a string and parses it into a vector of tokens
std::vector<Calc::Token> Calc::tokenise(const std::string& expression) {
  const std::vector<char> symbols = {'+', '-', '*', '/', '(', ')'};
  std::vector<Token> tokens {};
  for (std::size_t i =0; i < expression.size(); ++i) {
    const char c = expression[i];
    // check if c is one of '+', '-', '*', '/', '(', ')'
    if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
      tokens.push_back({c});
    } else if (isdigit(c)) {
      // process multiple digit integers
      std::string num {c};
      while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
        ++i;
        num.push_back(expression[i]);
      }
      tokens.push_back({'n', std::stoi(num)});
    }
  }
  return tokens;
}

// eval puts the pieces together to take a string with an
// arithmetic expression and output its evaluation
int Calc::eval(const std::string& expression) {
  std::vector<Token> tokens = tokenise(expression);
  std::vector<Token> postfix = infixToPostfix(tokens);
  return evalPostfix(postfix);
}
