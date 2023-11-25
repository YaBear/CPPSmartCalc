#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_VALIDATOR_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_VALIDATOR_H_

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>

namespace s21 {

class Validator {
 public:
  Validator(){};

  bool IsValid(std::string expression, double x_value) {
    expression = RemoveSpaces(expression);
    expression = ReplaceX(expression, x_value);
    if (expression[0] == '*' || expression[0] == '/' || expression[0] == '^' ||
        expression[0] == ')' || expression[0] == 'm' || expression == "") {
      return false;
    }
    size_t pos = 0;
    size_t left_bracket_count = 0;
    size_t right_bracket_count = 0;
    size_t max_size = expression.size();
    size_t number_count = 0;
    while (pos < max_size) {
      if (isdigit(expression[pos])) {
        size_t end_pos = pos;
        if (expression[pos - 1] == ')') return false;
        end_pos = DigitCheck(expression, end_pos);
        if (end_pos == 0) return false;
        pos = end_pos;
        ++number_count;
      } else if (isalpha(expression[pos])) {
        size_t end_pos = pos;
        while (end_pos < expression.size() && isalpha(expression[end_pos])) {
          ++end_pos;
        }
        std::string func = expression.substr(pos, end_pos - pos);
        if (!IsFunction(func)) return false;
        if (isdigit(expression[pos - 1]) && func != "mod") return false;
        pos = end_pos;
        if (func == "mod" && !ModCheck(expression, pos)) return false;
        if (func != "mod" && pos <= max_size && expression[pos] != '(')
          return false;
      } else if (expression[pos] == '(') {
        ++left_bracket_count;
        ++pos;
        if (pos < max_size &&
            (expression[pos] == '*' || expression[pos] == '/' ||
             expression[pos] == '^' || expression[pos] == 'd')) {
          return false;
        }
      } else if (expression[pos] == ')') {
        ++right_bracket_count;
        ++pos;
      } else {
        if (pos > 0 && IsOperator(expression[pos - 1])) return false;
        if (!IsOperator(expression[pos])) return false;
        ++pos;
      }
    }
    if (IsOperator(expression[expression.size() - 1])) return false;
    if (left_bracket_count != right_bracket_count) return false;
    if (number_count == 0) return false;
    return true;
  };

 private:
  std::unordered_set<char> operators_ = {'+', '-', '*', '/', '^'};
  std::unordered_set<std::string> functions_ = {
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "log", "ln", "mod"};

  bool IsOperator(const char token) {
    return operators_.find(token) != operators_.end();
  };

  bool IsFunction(const std::string token) {
    return functions_.find(token) != functions_.end();
  };

  std::string RemoveSpaces(std::string expression) {
    for (auto it = expression.begin(); it != expression.end(); ++it) {
      if (*it == ' ') {
        expression.erase(it);
        if (it >= expression.begin()) --it;
      }
    }
    return expression;
  };

  size_t DigitCheck(std::string expression, size_t end_pos) {
    size_t dot_count = 0;
    while (end_pos < expression.size() &&
           (isdigit(expression[end_pos]) || expression[end_pos] == '.')) {
      if (expression[end_pos] == '.') ++dot_count;
      if (dot_count > 1) {
        return 0;
      }
      ++end_pos;
      if (expression[end_pos] == 'e' || expression[end_pos] == 'E') {
        if (expression[end_pos + 1] == '-' || expression[end_pos + 1] == '+') {
          end_pos += 2;
        } else {
          return 0;
        }
      }
    }
    return end_pos;
  };

  bool ModCheck(std::string expression, size_t pos) {
    if (isdigit(expression[pos]) || expression[pos] == '(') {
      if (isdigit(expression[pos - 4]) || expression[pos - 4] == ')') {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  };

  std::string ReplaceX(std::string expression, double x_value) {
    std::ostringstream result;
    size_t pos = 0;
    while (pos < expression.length()) {
      size_t found = expression.find('x', pos);
      if (found != std::string::npos) {
        result << expression.substr(pos, found - pos);
        result << x_value;
        pos = found + 1;
      } else {
        result << expression.substr(pos);
        break;
      }
    }
    return result.str();
  }
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_VALIDATOR_H_
