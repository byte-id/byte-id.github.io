#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "calc.hpp"
#include <exception>
#include <cmath>

// Functions implemented
// Floating numbers/doubles
// Exponentiation
// Implied multiplication brackets

std::ostream& Calc::operator<<(std::ostream& out, const Calc::Token& t) {
  out << "{'" << t.type << "', " << t.val << '}';
  return out;
}

bool Calc::operator==(const Calc::Token& a, const Calc::Token& b) {
  if (a.type != b.type) return false;
  if (a.type == 'n') return a.val == b.val;
  return true;
}

// Function for precedence of operators, ^ highest
static int precedence(char type) {
  auto prec = 0;
  if (type == '^') prec = 4;
  if (type == '*' || type == '/') prec = 3;
  if (type == '+' || type == '-') prec = 2;
  return prec;
}

std::vector<Calc::Token> Calc::infixToPostfix(const std::vector<Token>& input) {
  std::vector<Token> output;
  std::vector<Token> operatorStack;
  for (Token t : input) {
    if (t.type == 'n') {
      output.push_back(t);
      } else if (t.type =='(') {
        operatorStack.push_back(t);
      } else if (t.type == ')') {
        while (!operatorStack.empty() && operatorStack.back().type != '(') {
          output.push_back(operatorStack.back());
          operatorStack.pop_back(); 
        }
        if (!operatorStack.empty()) {
          operatorStack.pop_back(); 
        }
      } else {
        while (!operatorStack.empty() && operatorStack.back().type != '(') {
         const char stype = operatorStack.back().type;
         // Rigth associative, true if current token (t) type is ^
         const bool expRA = t.type == '^';
         // Precedence of t and operatorStack element
         const int sprec = precedence(stype);
         const int tprec = precedence(t.type);

          // Right associtive vs left associative for > vs >=
         if ((expRA && sprec > tprec) || (!expRA && sprec >= tprec)) {
          output.push_back(operatorStack.back());
          operatorStack.pop_back();
          } else {
            break;
          }
        }
        operatorStack.push_back(t);
      }

  }
  output.insert(output.end(), operatorStack.rbegin(), operatorStack.rend());
  // while (!operatorStack.empty()) {
  //   output.push_back(operatorStack.back());
  //   operatorStack.pop_back();
  // }
  return output;
}

// Not much changed, only the format, and ^ added
double Calc::evalPostfix(const std::vector<Token>& tokens) {
  if (tokens.empty()) {
    return 0;
  }
  std::vector<double> stack;
  for (Token t : tokens) {
    if (t.type == 'n') {
      stack.push_back(t.val);
    } else {
      double val = 0;
      double a = stack.back();
      double b = *(stack.end()-2);
      switch (t.type) {
        case '+': val = (a + b); break;
        case '-': val = (b - a); break;
        case '*': val = (a * b); break;
        case '/': 
          if (a == 0) throw std::runtime_error("divide by zero");
          val = (b / a);
          break;
        case '^': val = pow(b, a); break; // Use pow from cmath library for exponentiation, otherwise loop
        default: throw std::runtime_error("Invalid operator/token");
      }
      stack.pop_back();
      stack.pop_back();
      stack.push_back(val);
    }
  }
  return stack.back();
}

std::vector<Calc::Token> Calc::tokenise(const std::string& expression) {
  const std::vector<char> symbols = {'+', '-', '*', '/', '^', '(', ')'};
  std::vector<Token> tokens {};
  for (std::size_t i =0; i < expression.size(); ++i) {
    // Get current char
    const char c = expression[i];
    // Handles/skips whitespace characters
    if (isspace(c)) continue;

    // Check for implied multiplication, if no operator between, ie 5(3+4), brackets -> *
    // If previous token is n and current char is '('
    // or if previous token is ')' and current char is n or '('
    if (!tokens.empty() && 
        ((tokens.back().type == 'n' && c == '(')
        || (tokens.back().type == ')' && 
        (c == '(' || isdigit(c) || c == '.')))) {
      // Add * token/operator
      tokens.push_back({'*'});
    }

    // check if c is an operator
    if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
      tokens.push_back({c});
    } else if (isdigit(c)) {
      // Process multiple digit numbers
      // String to build number
      std::string num;
      num += c;

      // To handle decimal numbers correctly
      while (++i < expression.size()) {
        char next = expression[i];
        // Checks if current char is a digit or '.'
        if (isdigit(next) || next == '.') {
          num += next;
        } else {
          // Move index back to non-digit char
          i--;
          break;
        }
      }
      // Convert number string to double, add token to vector
      tokens.push_back({'n', std::stod(num)});
    } 
  }
  return tokens;
}


double Calc::eval(const std::string& expression) {
  std::vector<Token> tokens = tokenise(expression);
  std::vector<Token> postfix = infixToPostfix(tokens);
  return evalPostfix(postfix);
}
