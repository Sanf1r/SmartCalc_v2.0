#include "Controller.h"

std::pair<bool, double> s21::Controller::Result(std::string string, double x) {
  return std::pair(model_->FinalCalculation(&string, x), model_->GetData());
}

bool s21::Controller::Graph(std::string string, double step, double left_x,
                            double right_x, double top_y, double buttom_y) {
  return model_->MakingGraph(&string, step, left_x, right_x, top_y, buttom_y);
}

void s21::Controller::Credit(double loan, double term, double rate, int month,
                             int mode) {
  model_->FinalCredit(loan, term, rate, month, mode);
}

const std::vector<double>& s21::Controller::GetX() { return model_->GetX(); }

const std::vector<double>& s21::Controller::GetY() { return model_->GetY(); }

double s21::Controller::GetMonthPay() { return model_->GetMonthPay(); }

double s21::Controller::GetMax() { return model_->GetMax(); }

double s21::Controller::GetMin() { return model_->GetMin(); }

double s21::Controller::GetOverpay() { return model_->GetOverpay(); }

double s21::Controller::GetTotal() { return model_->GetTotal(); }
