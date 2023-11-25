#include "controller.h"

namespace s21 {
Controller::Controller() {}

std::string Controller::CalculateResult(std::string expression,
                                        double x_value) {
  if (model_->Validation(expression, x_value)) {
    model_->Convertation(expression, x_value);
    model_->Calculation(expression);
    return model_->GetResult();
  } else {
    return "Error validation";
  }
}
}  // namespace s21
