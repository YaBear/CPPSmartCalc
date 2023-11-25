#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_POLISHNOTATIONMODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_POLISHNOTATIONMODEL_H_

#include "calculate.h"
#include "converter.h"
#include "validator.h"

namespace s21 {

class PolishNotationModel {
 public:
  PolishNotationModel(){};

  bool Validation(std::string expression, double x_value) {
    return ValidService_.IsValid(expression, x_value);
  };

  void Convertation(std::string &expression, double x_value) {
    expression = ConvService_.InfixToRPN(expression, x_value);
  };

  void Calculation(std::string expression) {
    CalcService_.Calculation(expression);
    result_ = CalcService_.GetResult();
  };

  std::string GetResult() { return result_; };

 private:
  Calculate CalcService_;
  Converter ConvService_;
  Validator ValidService_;
  std::string result_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_POLISHNOTATIONMODEL_H_
