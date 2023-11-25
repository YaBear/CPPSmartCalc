#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATE_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATE_H_

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>

namespace s21 {

class Calculate {
 public:
  Calculate() : result_(""){};

  void Calculation(const std::string expression) {
    result_.clear();
    size_t pos = 0;
    result_ = "";
    while (pos < expression.size()) {
      if (expression[pos] == ' ') {
        pos++;
        continue;
      }

      if (isdigit(expression[pos])) {
        pos = CheckDigit(expression, pos);
      } else if (IsOperator(expression[pos])) {
        Operands(expression, pos);
        pos++;
      } else if (isalpha(expression[pos])) {
        size_t end_pos = pos;
        while (end_pos < expression.size() && isalpha(expression[end_pos])) {
          end_pos++;
        }
        std::string func = expression.substr(pos, end_pos - pos);
        Functions(func);
        pos = end_pos;
      }
    }

    if (!std::isfinite(numbers_.top())) {
      result_ = "Error calculation";
    } else {
      SetResult();
    }
    numbers_.pop();
  };

  std::string GetResult() { return result_; };

 private:
  std::unordered_set<char> operators_ = {'+', '-', '*', '/', '^'};
  std::string result_;
  std::stack<double> numbers_;

  size_t CheckDigit(std::string expression, size_t pos) {
    std::string current_number;
    size_t end_pos = pos;
    while (end_pos < expression.size() &&
           (isdigit(expression[end_pos]) || expression[end_pos] == '.')) {
      end_pos++;
      if ((expression[end_pos] == 'e' || expression[end_pos] == 'E') &&
          (expression[end_pos + 1] == '-' || expression[end_pos + 1] == '+')) {
        end_pos += 2;
      }
    }
    current_number += expression.substr(pos, end_pos - pos);
    numbers_.push(std::stod(current_number));
    current_number = "";
    return end_pos;
  };

  bool IsOperator(const char token) {
    return operators_.find(token) != operators_.end();
  };

  void Operands(const std::string expression, size_t pos) {
    if (expression[pos] == '+') {
      double second_value = numbers_.top();
      numbers_.pop();
      double first_value = numbers_.top();
      numbers_.pop();
      numbers_.push(first_value + second_value);
    } else if (expression[pos] == '-') {
      double second_value = numbers_.top();
      numbers_.pop();
      double first_value = numbers_.top();
      numbers_.pop();
      numbers_.push(first_value - second_value);
    } else if (expression[pos] == '*') {
      double second_value = numbers_.top();
      numbers_.pop();
      double first_value = numbers_.top();
      numbers_.pop();
      numbers_.push(first_value * second_value);
    } else if (expression[pos] == '/') {
      double second_value = numbers_.top();
      numbers_.pop();
      double first_value = numbers_.top();
      numbers_.pop();
      numbers_.push(first_value / second_value);
    } else if (expression[pos] == '^') {
      double second_value = numbers_.top();
      numbers_.pop();
      double first_value = numbers_.top();
      numbers_.pop();
      numbers_.push(pow(first_value, second_value));
    }
  };

  void Functions(const std::string function) {
    double current_number = 0;
    if (function == "unaryplus") {
      double value = numbers_.top();
      numbers_.pop();
      numbers_.push(value);
    } else if (function == "unaryminus") {
      double value = numbers_.top();
      numbers_.pop();
      numbers_.push(-value);
    } else if (function == "cos") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(cos(current_number));
    } else if (function == "sin") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(sin(current_number));
    } else if (function == "tan") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(tan(current_number));
    } else if (function == "acos") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(acos(current_number));
    } else if (function == "asin") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(asin(current_number));
    } else if (function == "atan") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(atan(current_number));
    } else if (function == "sqrt") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(sqrt(current_number));
    } else if (function == "log") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(log10(current_number));
    } else if (function == "ln") {
      current_number = numbers_.top();
      numbers_.pop();
      numbers_.push(log(current_number));
    } else if (function == "mod") {
      current_number = numbers_.top();
      numbers_.pop();
      double temp_number = numbers_.top();
      numbers_.pop();
      numbers_.push(fmod(temp_number, current_number));
    }
  };

  void SetResult() {
    std::ostringstream out_return;
    out_return.precision(7);
    out_return << std::fixed << numbers_.top();
    result_ = std::move(out_return).str();
    size_t pos = result_.find_last_not_of('0');
    if (pos != std::string::npos && result_[pos] == '.') {
      --pos;
    }
    result_ = result_.substr(0, pos + 1);
  };
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATE_H_
