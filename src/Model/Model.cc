#include "Model.h"

#include <iostream>

bool s21::Model::FinalCalculation(std::string* string, double x) {
  bool code = true;
  ClearModel();
  FindUnary(string);
  StringMorph(string);
  // for (auto i : *string) std::cout << i;  // ---- FOR DEBUG
  MakingLexems(string);
  if (BracketCount("(") != BracketCount(")") || InfixToRpn() || RpnAnswer(x)) {
    code = false;
  }
  return code;
}

bool s21::Model::MakingGraph(std::string* string, double step, double left_x,
                             double right_x, double buttom_y, double top_y) {
  bool code = true;
  if (AxisCheck(left_x, right_x) || AxisCheck(buttom_y, top_y) ||
      !FinalCalculation(string, left_x)) {
    code = false;
  } else {
    unsigned int N = ((right_x - left_x) / step) + 1;
    double c = left_x;
    for (unsigned int i = 0; i < N; ++i) {
      data_ = 0;
      RpnAnswer(c);
      x_.push_back(c);
      if (data_ <= buttom_y || data_ >= top_y) {
        y_.push_back(std::nan(""));
      } else {
        y_.push_back(data_);
      }
      c += step;
    }
  }
  return code;
}

void s21::Model::FinalCredit(double loan, double term, double rate, int month,
                             int mode) {
  if (month) term *= 12;
  if (mode) {
    DiffCreditCalc(loan, term, rate);
  } else {
    CreditCalc(loan, term, rate);
  }
}

double s21::Model::GetData() { return data_; }
double s21::Model::GetMonthPay() { return month_pay_; }
double s21::Model::GetMax() { return max_; }
double s21::Model::GetMin() { return min_; }
double s21::Model::GetOverpay() { return overpay_; }
double s21::Model::GetTotal() { return total_pay_; }
const std::vector<double>& s21::Model::GetX() { return x_; }
const std::vector<double>& s21::Model::GetY() { return y_; }

void s21::Model::ClearModel() {
  data_ = 0.0;
  lexems_.clear();
  temp_out_.clear();
  RPN_.clear();
  x_.clear();
  y_.clear();
}

void s21::Model::FindUnary(std::string* string) {
  string->reserve(string->size() * 5);
  for (auto i = string->begin(); i != string->end(); ++i) {
    if (*i == '-' &&
        (i == string->begin() || *(i - 1) == '^' || *(i - 1) == '(')) {
      string->replace(i, i + 1, "(0-1)*");
    } else if (*i == '+' &&
               (i == string->begin() || *(i - 1) == '^' || *(i - 1) == '(')) {
      string->replace(i, i + 1, "(0+1)*");
    }
  }
  string->shrink_to_fit();
}

void s21::Model::StringMorph(std::string* string) {
  string->reserve(string->size() * 5);
  for (auto i = string->begin(); i != string->end(); ++i) {
    if (*i == '*') {
      string->replace(i, i + 1, "|*|");
      i += 2;
    } else if (*i == '/') {
      string->replace(i, i + 1, "|/|");
      i += 2;
    } else if (*i == '^') {
      string->replace(i, i + 1, "|^|");
      i += 2;
    } else if (*i == '(') {
      string->replace(i, i + 1, "|(|");
      i += 2;
    } else if (*i == ')') {
      string->replace(i, i + 1, "|)|");
      i += 2;
    } else if (*i == '+') {
      string->replace(i, i + 1, "|+|");
      i += 2;
    } else if (*i == '-') {
      string->replace(i, i + 1, "|-|");
      i += 2;
    } else if (*i == 'm') {
      string->replace(i, i + 3, "|mod|");
      i += 4;
    }
  }
  string->shrink_to_fit();
}

void s21::Model::MakingLexems(std::string* str) {
  std::string temp;
  std::istringstream ss(*str);
  while (std::getline(ss, temp, '|')) {
    if (!temp.empty()) lexems_.push_back(temp);
  }
}

int s21::Model::IsNum(std::string string) {
  int code = 1;
  for (auto i = string.begin(); i != string.end(); ++i) {
    if ((*i == '-' || *i == '+') && string.size() == 1) {
      code = 0;
      break;
    }
    if (*i != '.' && *i != '0' && *i != '1' && *i != '2' && *i != '3' &&
        *i != '4' && *i != '5' && *i != '6' && *i != '7' && *i != '8' &&
        *i != '9' && *i != '-' && *i != '+' && *i != 'X' && *i != 'e') {
      code = 0;
      break;
    }
  }
  return code;
}

int s21::Model::IsFunc(const std::string& string) {
  int code = 0;
  if ((string == "sin") || (string == "cos") || (string == "tan") ||
      (string == "asin") || (string == "acos") || (string == "atan") ||
      (string == "sqrt") || (string == "ln") || (string == "log")) {
    code = 1;
  }
  return code;
}

int s21::Model::IsOp(const std::string& string) {
  int code = 0;
  if ((string == "+") || (string == "-") || (string == "*") ||
      (string == "/") || (string == "^") || (string == "mod")) {
    code = 1;
  }
  return code;
}

int s21::Model::Score(const std::string& string) {
  int result = 0;
  if (string == "-" || string == "+") result = 1;
  if (string == "/" || string == "*" || string == "mod") result = 2;
  if (string == "^") result = 3;
  if (string == "sin" || string == "cos" || string == "tan" ||
      string == "asin" || string == "acos" || string == "atan" ||
      string == "sqrt" || string == "ln" || string == "log") {
    result = 5;
  }
  return result;
}

int s21::Model::NeedForOp(char op) {
  int result;
  switch (op) {
    case '+':
    case '*':
    case '-':
    case '/':
    case '^':
    case 'm':
      result = 2;
      break;
    case 's':
    case 'c':
    case 't':
    case 'a':
    case 'l':
      result = 1;
      break;
  }
  return result;
}

int s21::Model::InfixToRpn() {
  int code = OK;
  std::stack<std::string> stack;
  for (auto i = lexems_.begin(); i != lexems_.end(); ++i) {
    std::string token(*i);
    if (IsNum(token)) {
      temp_out_.push_back(token);
    } else if (IsFunc(token) || token == "(") {
      stack.push(token);
    } else if (!stack.empty() && token == ")") {
      while (!stack.empty() && !(stack.top() == "(")) {
        temp_out_.push_back(stack.top());
        stack.pop();
      }
      if (!stack.empty()) stack.pop();
    } else if (IsOp(token)) {
      int score = Score(token);
      if (!stack.empty()) {
        while (!stack.empty() && !(token == "^" && stack.top() == "^") &&
               Score(stack.top()) >= score) {
          temp_out_.push_back(stack.top());
          stack.pop();
        }
      }
      stack.push(token);
    } else {
      code = CALCULATION_ERROR;
      break;
    }
  }
  if (code == OK) {
    for (auto i = temp_out_.begin();;) {
      if (i != temp_out_.end()) {
        RPN_.push_back(*i++);
      } else if (!stack.empty()) {
        RPN_.push_back(stack.top());
        stack.pop();
      } else {
        break;
      }
    }
  }

  return code;
}

double s21::Model::OperationEval(char op, char dop, std::stack<double>* head) {
  double temp;
  double result;
  switch (op) {
    case '+':
      temp = head->top();
      head->pop();
      result = temp + head->top();
      head->pop();
      break;
    case '*':
      temp = head->top();
      head->pop();
      result = temp * head->top();
      head->pop();
      break;
    case '-':
      temp = head->top();
      head->pop();
      result = head->top() - temp;
      head->pop();
      break;
    case '/':
      temp = head->top();
      head->pop();
      result = head->top() / temp;
      head->pop();
      break;
    case '^':
      temp = head->top();
      head->pop();
      result = std::pow(head->top(), temp);
      head->pop();
      break;
    case 'm':
      temp = head->top();
      head->pop();
      result = std::fmod(head->top(), temp);
      head->pop();
      break;
    case 's':
      switch (dop) {
        case 'q':
          result = std::sqrt(head->top());
          head->pop();
          break;
        default:
          result = std::sin(head->top());
          head->pop();
          break;
      }
      break;
    case 'c':
      result = std::cos(head->top());
      head->pop();
      break;
    case 't':
      result = std::tan(head->top());
      head->pop();
      break;
    case 'a':
      switch (dop) {
        case 's':
          result = std::asin(head->top());
          head->pop();
          break;
        case 'c':
          result = std::acos(head->top());
          head->pop();
          break;
        case 't':
          result = std::atan(head->top());
          head->pop();
          break;
      }
      break;
    case 'l':
      switch (dop) {
        case 'n':
          result = std::log(head->top());
          head->pop();
          break;
        case 'o':
          result = std::log10(head->top());
          head->pop();
          break;
      }
      break;
  }
  return result;
}

int s21::Model::RpnAnswer(double x) {
  int code = 0;
  std::stack<double> head;
  int stacksize = 0;
  double temp;
  char op, dop = ' ';

  for (auto i = RPN_.begin(); i != RPN_.end(); i++) {
    std::string token = *i;
    if (IsNum(token)) {
      if (token == "X") {
        temp = x;
      } else {
        temp = std::stod(token);
      }
      head.push(temp);
      stacksize++;
    } else {
      op = token[0];
      if (stacksize < NeedForOp(op)) {
        code = CALCULATION_ERROR;
        break;
      }
      if (token.size() > 1) dop = token[1];
      head.push(OperationEval(op, dop, &head));
      stacksize -= NeedForOp(op) - 1;
    }
  }
  if (stacksize == 1) {
    data_ = head.top();
    head.pop();
  } else {
    code = CALCULATION_ERROR;
    while (stacksize) {
      head.pop();
      stacksize--;
    }
  }
  return code;
}

int s21::Model::BracketCount(const std::string& f) {
  int count = 0;
  for (auto i = lexems_.begin(); i != lexems_.end(); ++i) {
    if (*i == f) ++count;
  }
  return count;
}

int s21::Model::AxisCheck(double a, double b) {
  int code = OK;
  if (a > b) code = CALCULATION_ERROR;
  return code;
}

void s21::Model::CreditCalc(double loan, double term, double rate) {
  double month_rate = rate / 12 / 100;
  double ann_cof = (month_rate * powl(1 + month_rate, term)) /
                   (powl(1 + month_rate, term) - 1);
  double payment = ann_cof * loan;
  month_pay_ = payment;
  overpay_ = payment * term - loan;
  total_pay_ = loan + overpay_;
}

void s21::Model::DiffCreditCalc(double loan, double term, double rate) {
  double month_rate = rate / 12 / 100;
  double payment = loan / term;
  double result, total;
  result = payment + (loan - payment * 0) * month_rate;
  max_ = min_ = total = result;
  for (int i = 1; i < term; ++i) {
    result = payment + (loan - payment * i) * month_rate;
    if (result > max_) max_ = result;
    if (result < min_) min_ = result;
    total += result;
  }
  overpay_ = total - loan;
  total_pay_ = loan + overpay_;
}
