#include <gtest/gtest.h>

#include "../Model/Model.h"

s21::Model test;

TEST(calc, 01) {
  std::string str = "1+2+3+4*7*8^3^2";
  test.FinalCalculation(&str, 0);
  ASSERT_EQ(test.GetData(), 3758096390);
}

TEST(calc, 02) {
  std::string str = "-1*(888.22*sin(888-(+6))/(85-6))";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), -7.9671827, 1e-7);
}

TEST(calc, 03) {
  std::string str = "-1*(888.22*sin((888-(+6))^3)/(85-6))";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 8.8517682, 1e-7);
}

TEST(calc, 04) {
  std::string str = "6.3*(7.2-sqrt(5.6))*6mod2";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 0.7088736, 1e-7);
}

TEST(calc, 05) {
  std::string str = "sin(5)*cos(10)-tan(10)";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 0.1562452, 1e-7);
}

TEST(calc, 06) {
  std::string str = "asin(0.68)*acos(-0.2224)*atan(0.00005)";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 0.0000671, 1e-7);
}

TEST(calc, 07) {
  std::string str = "log(0.68)*ln(0.2224)^1^1^2";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 0.2517856, 1e-7);
}

TEST(calc, 08) {
  std::string str = "(6.4*(6-2*(6^(2-0))))";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), -422.4, 1e-7);
}

TEST(calc, 09) {
  std::string str = "1+2";
  test.FinalCalculation(&str, 0);
  EXPECT_NEAR(test.GetData(), 3, 1e-7);
}

TEST(calc, 10) {
  std::string str = "1+X-X";
  test.FinalCalculation(&str, 1);
  EXPECT_NEAR(test.GetData(), 1, 1e-7);
}

TEST(calc, 11) {
  std::string str = "1+1-";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 12) {
  std::string str = "1+1-((1-1)";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 13) {
  std::string str = ")";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 14) {
  std::string str = "sin(X)";
  std::vector<double> y_result = {0.958924,  0.756802,  -0.14112, -0.909297,
                                  -0.841471, 0,         0.841471, 0.909297,
                                  0.14112,   -0.756802, -0.958924};
  std::vector<double> x_result = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
  bool res = test.MakingGraph(&str, 1, -5, 5, -5, 5);
  auto j = y_result.begin();
  for (auto i = test.GetY().begin(); i != test.GetY().end(); ++i, ++j) {
    EXPECT_NEAR(*i, *j, 1e-6);
  }
  auto z = x_result.begin();
  for (auto i = test.GetX().begin(); i != test.GetX().end(); ++i, ++z) {
    EXPECT_NEAR(*i, *z, 1e-6);
  }

  EXPECT_EQ(res, true);
}

TEST(calc, 15) {
  test.FinalCredit(1000, 12, 5, 0, 0);
  double res_month = 85.61;
  double res_over = 27.29;
  double res_total = 1027.29;
  EXPECT_NEAR(test.GetMonthPay(), res_month, 1e-2);
  EXPECT_NEAR(test.GetOverpay(), res_over, 1e-2);
  EXPECT_NEAR(test.GetTotal(), res_total, 1e-2);
}

TEST(calc, 16) {
  test.FinalCredit(1000, 12, 5, 0, 1);
  double res_min = 83.68;
  double res_max = 87.50;
  double res_over = 27.08;
  double res_total = 1027.08;
  EXPECT_NEAR(test.GetMin(), res_min, 1e-2);
  EXPECT_NEAR(test.GetMax(), res_max, 1e-2);
  EXPECT_NEAR(test.GetOverpay(), res_over, 1e-2);
  EXPECT_NEAR(test.GetTotal(), res_total, 1e-2);
}

TEST(calc, 17) {
  test.FinalCredit(1000, 12, 5, 0, 1);
  double res_min = 83.68;
  double res_max = 87.50;
  double res_over = 27.08;
  double res_total = 1027.08;
  EXPECT_NEAR(test.GetMin(), res_min, 1e-2);
  EXPECT_NEAR(test.GetMax(), res_max, 1e-2);
  EXPECT_NEAR(test.GetOverpay(), res_over, 1e-2);
  EXPECT_NEAR(test.GetTotal(), res_total, 1e-2);
}

TEST(calc, 18) {
  std::string str = "1+1-+-";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 19) {
  std::string str = "1+1-12 12+-";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 20) {
  std::string str = "22sin50mod8";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 21) {
  std::string str = "1+(+1)";
  test.FinalCalculation(&str, 0);
  ASSERT_EQ(test.GetData(), 2);
}

TEST(calc, 22) {
  std::string str = "1 1 cos sin X";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 23) {
  std::string str = "1++1++ cos sin X";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 24) {
  std::string str = "(";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 25) {
  std::string str = "(+))";
  bool res = test.FinalCalculation(&str, 0);
  ASSERT_EQ(res, false);
}

TEST(calc, 26) {
  std::string str = "sin(X)";
  bool res = test.MakingGraph(&str, 1, 5, -5, 5, -5);

  EXPECT_EQ(res, false);
}