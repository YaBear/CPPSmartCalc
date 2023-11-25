#include "main.h"

TEST(ValidatorTest, Expression_Base) {
  s21::Validator test_val;
  std::string exp = "1 + 2 + 3 +4 +5 +  6";
  EXPECT_EQ(test_val.IsValid(exp, 0), true);
  std::string exp1 = "(1 + 2) * (1 + 2)";
  EXPECT_EQ(test_val.IsValid(exp1, 0), true);
  std::string exp2 = "-1 + 2";
  EXPECT_EQ(test_val.IsValid(exp2, 0), true);
  std::string exp3 = "(-9) - (-9)";
  EXPECT_EQ(test_val.IsValid(exp3, 0), true);
  std::string exp4 = "1++2+3";
  EXPECT_EQ(test_val.IsValid(exp4, 0), false);
  std::string exp5 = "(1+2) * )(1+2)";
  EXPECT_EQ(test_val.IsValid(exp5, 0), false);
  std::string exp6 = "1.2.3 + 1";
  EXPECT_EQ(test_val.IsValid(exp6, 0), false);
  std::string exp7 = "1e-2 + 2";
  EXPECT_EQ(test_val.IsValid(exp7, 0), true);
  std::string exp8 = "1e*2 + 3";
  EXPECT_EQ(test_val.IsValid(exp8, 0), false);
}

TEST(ValidatorTest, Expression_Long) {
  s21::Validator test_val;
  std::string exp =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  EXPECT_EQ(test_val.IsValid(exp, 0), true);
  std::string exp1 =
      "acos(-(0+1))+asin(sqrt(81)-8.321)-atan(123mod(5-2)+0.123)";
  EXPECT_EQ(test_val.IsValid(exp1, 0), true);
  std::string exp2 =
      "acossin(-(0+1))+asincos(qrt(81)-8.321)-tg(123mod(5-2)+0.123)";
  EXPECT_EQ(test_val.IsValid(exp2, 0), false);
}

TEST(ConverterTest, Expression_Base) {
  s21::Converter test_cv;
  std::string exp = "1 + 2 + 3 + 4";
  std::string rpn = test_cv.InfixToRPN(exp, 0);
  EXPECT_EQ(rpn, "1 2 + 3 + 4 + ");
  std::string exp1 = "(-1) * 2 + 3.1 - (303e-1 ^ 2)";
  std::string rpn1 = test_cv.InfixToRPN(exp1, 0);
  EXPECT_EQ(rpn1, "1 unaryminus 2 * 3.1 + 303e-1 2 ^ - ");
  std::string exp2 = "sin(3.14) - cos(3.14)";
  std::string rpn2 = test_cv.InfixToRPN(exp2, 0);
  EXPECT_EQ(rpn2, "3.14 sin 3.14 cos - ");
  std::string exp3 = "x + 2 - (x ^ 2)";
  std::string rpn3 = test_cv.InfixToRPN(exp3, 3.14);
  EXPECT_EQ(rpn3, "3.14 2 + 3.14 2 ^ - ");
}

TEST(ConverterTest, Expression_Long) {
  s21::Converter test_cv;
  std::string exp =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  std::string rpn = test_cv.InfixToRPN(exp, 0);
  EXPECT_EQ(
      rpn,
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 1 1 + - / 3 * + 2 1 1 + + - * - ");
  std::string exp1 =
      "acos(-(0+1))+asin(sqrt(81)-8.321)-atan(123mod(5-2)+0.123)";
  std::string rpn1 = test_cv.InfixToRPN(exp1, 0);
  EXPECT_EQ(rpn1,
            "0 1 + unaryminus acos 81 sqrt 8.321 - asin + 123 5 2 - mod 0.123 "
            "+ atan - ");
  std::string exp2 = "cos(sin(tan(sqrt(atan(tan(acos(asin(3.14))))))))";
  std::string rpn2 = test_cv.InfixToRPN(exp2, 0);
  EXPECT_EQ(rpn2, "3.14 asin acos tan atan sqrt tan sin cos ");
}

TEST(CalculationTest, Expression_Base) {
  s21::PolishNotationModel pnm;
  std::string exp = "5+3+2+5+5+1+2+3+4+5+6+7+8+9";
  pnm.Convertation(exp, 0);
  pnm.Calculation(exp);
  ASSERT_DOUBLE_EQ(std::stod(pnm.GetResult()), 65);
  std::string exp1 = "5-3-2-5-5-1-2-3-4-5-6-7-8-9";
  pnm.Convertation(exp1, 0);
  pnm.Calculation(exp1);
  ASSERT_DOUBLE_EQ(std::stod(pnm.GetResult()), -55);
  std::string exp2 = "5143*1213*24532/1213/1445";
  pnm.Convertation(exp2, 0);
  pnm.Calculation(exp2);
  ASSERT_NEAR(std::stod(pnm.GetResult()), 87313.5474048, 1e-7);
  std::string exp3 = "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123";
  pnm.Convertation(exp3, 0);
  pnm.Calculation(exp3);
  ASSERT_NEAR(std::stod(pnm.GetResult()), 0.79973842646, 1e-7);
  std::string exp4 = "2^3^2";
  pnm.Convertation(exp4, 0);
  pnm.Calculation(exp4);
  ASSERT_DOUBLE_EQ(std::stod(pnm.GetResult()), 512);
  std::string exp5 = "x - 6";
  pnm.Convertation(exp5, 15);
  pnm.Calculation(exp5);
  ASSERT_DOUBLE_EQ(std::stod(pnm.GetResult()), 9);
  std::string exp6 = "2+x/x-x*(xmodx)";
  pnm.Convertation(exp6, 3);
  pnm.Calculation(exp6);
  ASSERT_DOUBLE_EQ(std::stod(pnm.GetResult()), 3);
}

TEST(CalculationTest, Expression_Long) {
  s21::PolishNotationModel pnm;
  std::string exp =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  pnm.Convertation(exp, 0);
  pnm.Calculation(exp);
  ASSERT_NEAR(std::stod(pnm.GetResult()), -30.0721649, 1e-7);
  std::string exp1 = "cos(2-sin(3+0.26*7+1))";
  pnm.Convertation(exp1, 0);
  pnm.Calculation(exp1);
  ASSERT_NEAR(std::stod(pnm.GetResult()), -0.7681865, 1e-7);
  std::string exp2 = "10*((-5)+log(2+(9/3)))";
  pnm.Convertation(exp2, 0);
  pnm.Calculation(exp2);
  ASSERT_NEAR(std::stod(pnm.GetResult()), -43.01029999, 1e-7);
  std::string exp3 = "-ln(tan(sqrt(50-1)))";
  pnm.Convertation(exp3, 0);
  pnm.Calculation(exp3);
  ASSERT_NEAR(std::stod(pnm.GetResult()), 0.1375991, 1e-7);
  std::string exp4 =
      "acos(-(0+1))+asin(sqrt(81)-8.321)-atan(123mod(5-2)+0.123)";
  pnm.Convertation(exp4, 0);
  pnm.Calculation(exp4);
  ASSERT_NEAR(std::stod(pnm.GetResult()), 3.76560701, 1e-7);
  std::string exp5 = "sin(sin(sin(sin(sin(90)))))";
  pnm.Convertation(exp5, 0);
  pnm.Calculation(exp5);
  ASSERT_NEAR(std::stod(pnm.GetResult()), 0.6023926, 1e-7);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}