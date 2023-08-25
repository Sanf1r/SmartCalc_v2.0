#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../Model/Model.h"
namespace s21 {
class Controller {
 public:
  // Default constructor
  explicit Controller(Model* m) : model_(m){};
  // Public method for RPN calculation of input string
  std::pair<bool, double> Result(std::string string, double x);
  // Public method for graph calculation
  bool Graph(std::string string, double step, double left_x, double right_x,
             double top_y, double buttom_y);
  // Public method for credit calculations
  void Credit(double loan, double term, double rate, int month, int mode);
  // Getters
  const std::vector<double>& GetX();
  const std::vector<double>& GetY();
  double GetMonthPay();
  double GetMax();
  double GetMin();
  double GetOverpay();
  double GetTotal();

 private:
  Model* model_;
};
}  // namespace s21

#endif
