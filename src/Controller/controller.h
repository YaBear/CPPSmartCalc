#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/PolishNotationModel.h"

namespace s21 {
class Controller {
 public:
  Controller();
  Controller(s21::PolishNotationModel *m) : model_(m){};

  std::string CalculateResult(std::string expression, double x_value);

 private:
  s21::PolishNotationModel *model_;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
