#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <cmath>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
enum ResultCode { OK, CALCULATION_ERROR };

class Model {
 public:
  // Default constructor
  Model()
      : data_(0), month_pay_(0), max_(0), min_(0), overpay_(0), total_pay_(0){};
  // Public method for RPN calculations
  bool FinalCalculation(std::string* string, double x);
  // Public method for graph calculation
  bool MakingGraph(std::string* string, double step, double left_x,
                   double right_x, double buttom_y, double top_y);
  // Public method for credit calculations
  void FinalCredit(double loan, double term, double rate, int month, int mode);
  // Getters
  double GetData();
  double GetMonthPay();
  double GetMax();
  double GetMin();
  double GetOverpay();
  double GetTotal();
  const std::vector<double>& GetX();
  const std::vector<double>& GetY();

 private:
  double data_;
  std::vector<double> x_;
  std::vector<double> y_;
  std::vector<std::string> lexems_;
  std::vector<std::string> temp_out_;
  std::vector<std::string> RPN_;
  double month_pay_ = 0, max_ = 0, min_ = 0, overpay_ = 0, total_pay_ = 0;

  // Private helpers methods
  void ClearModel();
  void FindUnary(std::string* string);
  void StringMorph(std::string* string);
  void MakingLexems(std::string* str);
  int IsNum(std::string string);
  int IsFunc(const std::string& string);
  int IsOp(const std::string& string);
  int Score(const std::string& string);
  int NeedForOp(char op);
  int InfixToRpn();
  double OperationEval(char op, char dop, std::stack<double>* head);
  int RpnAnswer(double x);
  int BracketCount(const std::string&);
  int AxisCheck(double a, double b);
  void CreditCalc(double loan, double term, double rate);
  void DiffCreditCalc(double loan, double term, double rate);
};

}  // namespace s21

#endif
