#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CONVERTER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CONVERTER_H_

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>

namespace s21 {

class Converter {
 public:
  Converter() : rpn_(""){};

  std::string InfixToRPN(std::string infix, double x_value) {
    rpn_.clear();
    infix = ReplaceX(infix, x_value);
    std::stack<std::string> operators;
    size_t pos = 0;
    while (pos < infix.size()) {
      if (infix[pos] == ' ') {
        pos++;
        continue;
      }

      if (isdigit(infix[pos])) {
        pos = CheckDigit(infix, pos);
      } else if (isalpha(infix[pos])) {
        size_t end_pos = pos;
        while (end_pos < infix.size() && isalpha(infix[end_pos])) {
          end_pos++;
        }
        std::string func = infix.substr(pos, end_pos - pos);
        operators.push(func);
        pos = end_pos;
      } else if (infix[pos] == '(') {
        operators.push("(");
        pos++;
      } else if (infix[pos] == ')') {
        while (!operators.empty() && operators.top() != "(") {
          rpn_ += operators.top() + ' ';
          operators.pop();
        }
        operators.pop();
        pos++;
      } else {
        CheckOperand(infix, pos, operators);
        pos++;
      }
    }

    while (!operators.empty()) {
      rpn_ += operators.top() + ' ';
      operators.pop();
    }
    return rpn_;
  };

 private:
  std::unordered_map<std::string, int> precedence_ = {
      {"+", 1},    {"-", 1},    {"*", 2},   {"/", 2},    {"^", 4},
      {"cos", 4},  {"sin", 4},  {"tan", 4}, {"acos", 4}, {"asin", 4},
      {"atan", 4}, {"sqrt", 4}, {"log", 4}, {"ln", 4},   {"mod", 2}};
  std::string rpn_;

  void CheckOperand(std::string infix, size_t pos,
                    std::stack<std::string> &operators) {
    std::string op(1, infix[pos]);
    if (pos == 0 || (pos > 0 && infix[pos - 1] == '(')) {
      if (op == "-") {
        op = "unaryminus";
      } else if (op == "+") {
        op = "unaryplus";
      }
    }
    while (!operators.empty() && IsOperator(operators.top()) &&
           (precedence_[op] < precedence_[operators.top()] ||
            (precedence_[op] == precedence_[operators.top()] &&
             infix[pos] != '^'))) {
      rpn_ += operators.top() + ' ';
      operators.pop();
    }
    operators.push(op);
  };

  size_t CheckDigit(std::string infix, size_t pos) {
    size_t end_pos = pos;
    while (end_pos < infix.size() &&
           (isdigit(infix[end_pos]) || infix[end_pos] == '.')) {
      end_pos++;
      if ((infix[end_pos] == 'e' || infix[end_pos] == 'E') &&
          (infix[end_pos + 1] == '-' || infix[end_pos + 1] == '+')) {
        end_pos += 2;
      }
    }
    rpn_ += infix.substr(pos, end_pos - pos) + ' ';
    return end_pos;
  };

  bool IsOperator(const std::string token) {
    return precedence_.find(token) != precedence_.end();
  };

  std::string ReplaceX(std::string expression, double x_value) {
    std::ostringstream result;
    size_t pos = 0;
    while (pos < expression.length()) {
      size_t found = expression.find('x', pos);
      if (found != std::string::npos) {
        result << expression.substr(pos, found - pos);
        result << "(" << x_value << ")";
        pos = found + 1;
      } else {
        result << expression.substr(pos);
        break;
      }
    }
    return result.str();
  };
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CONVERTER_H_
