#include "View.h"

#include "./ui_View.h"
#include "./ui_ViewCredit.h"

s21::CreditWindow::CreditWindow(Controller *c, QWidget *parent)
    : QWidget(parent), controller_(c), ui_(new Ui::CreditWindow) {
  ui_->setupUi(this);
  setFixedSize(480, 560);
  connect(ui_->pushButton_return, SIGNAL(released()), this,
          SLOT(OnPushButtonReturnReleased()));
  connect(ui_->pushButton_calc, SIGNAL(released()), this,
          SLOT(OnPushButtonCalcReleased()));
}

s21::CreditWindow::~CreditWindow() { delete ui_; }

void s21::CreditWindow::OnPushButtonReturnReleased() {
  this->close();
  emit BaseWindow();
}

void s21::CreditWindow::OnPushButtonCalcReleased() {
  ui_->Monthly_cur->setText(ui_->cur->currentText());
  ui_->Over_cur->setText(ui_->cur->currentText());
  ui_->Total_cur->setText(ui_->cur->currentText());
  controller_->Credit(
      ui_->loan->text().toDouble(), ui_->term->text().toDouble(),
      ui_->rate->text().toDouble(), ui_->term_kind->currentIndex(),
      ui_->Credit_type->currentIndex());
  if (ui_->Credit_type->currentIndex() == 0) {
    ui_->Monthly_line->setText(
        QString::number(controller_->GetMonthPay(), 'f', 2));
  } else {
    ui_->Monthly_line->setText(QString::number(controller_->GetMax(), 'f', 2) +
                               " .. " +
                               QString::number(controller_->GetMin(), 'f', 2));
  }
  ui_->Over_line->setText(QString::number(controller_->GetOverpay(), 'f', 2));
  ui_->Total_line->setText(QString::number(controller_->GetTotal(), 'f', 2));
}

s21::MainWindow::MainWindow(Controller *c, QWidget *parent)
    : QMainWindow(parent), controller_(c), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  setFixedSize(430, 610);
  credit_window_ = new CreditWindow(c);
  connect(credit_window_, &s21::CreditWindow::BaseWindow, this,
          &s21::MainWindow::show);
  connect(ui_->pushButton_0, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_1, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_2, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_3, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_4, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_5, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_6, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_7, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_8, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_9, SIGNAL(released()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_Sign, SIGNAL(released()), this, SLOT(Operations()));
  connect(ui_->pushButton_Plus, SIGNAL(released()), this,
          SLOT(MathOperations()));
  connect(ui_->pushButton_Minus, SIGNAL(released()), this,
          SLOT(MathOperations()));
  connect(ui_->pushButton_Mul, SIGNAL(released()), this,
          SLOT(MathOperations()));
  connect(ui_->pushButton_Div, SIGNAL(released()), this,
          SLOT(MathOperations()));
  connect(ui_->pushButton_mod, SIGNAL(released()), this,
          SLOT(MathOperations()));
  connect(ui_->pushButton_sqrt, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_ln, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_log, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_sin, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_cos, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_tan, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_asin, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_acos, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_atan, SIGNAL(released()), this, SLOT(Functions()));
  connect(ui_->pushButton_Dot, SIGNAL(released()), this,
          SLOT(OnPushButtonDotReleased()));
  connect(ui_->pushButton_AC, SIGNAL(released()), this,
          SLOT(OnPushButtonAcReleased()));
  connect(ui_->pushButton_Eq, SIGNAL(released()), this,
          SLOT(OnPushButtonEqReleased()));
  connect(ui_->pushButton_left, SIGNAL(released()), this,
          SLOT(OnPushButtonLeftReleased()));
  connect(ui_->pushButton_right, SIGNAL(released()), this,
          SLOT(OnPushButtonRightReleased()));
  connect(ui_->pushButton_degree, SIGNAL(released()), this,
          SLOT(OnPushButtonDegreeReleased()));
  connect(ui_->pushButton_X, SIGNAL(released()), this,
          SLOT(OnPushButtonXReleased()));
  connect(ui_->radioButton_graph, SIGNAL(clicked(bool)), this,
          SLOT(OnRadioButtonGraphToggled(bool)));
  connect(ui_->pushButton_Graph, SIGNAL(released()), this,
          SLOT(OnPushButtonGraphReleased()));
  connect(ui_->pushButton_credit, SIGNAL(released()), this,
          SLOT(OnPushButtonCreditReleased()));
  connect(ui_->pushButton_e, SIGNAL(released()), this,
          SLOT(OnPushButtonEReleased()));
  PlotInit();
}

s21::MainWindow::~MainWindow() {
  delete ui_;
  delete credit_window_;
}

void s21::MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_0) {
    emit ui_->pushButton_0->released();
  } else if (event->key() == Qt::Key_1) {
    emit ui_->pushButton_1->released();
  } else if (event->key() == Qt::Key_2) {
    emit ui_->pushButton_2->released();
  } else if (event->key() == Qt::Key_3) {
    emit ui_->pushButton_3->released();
  } else if (event->key() == Qt::Key_4) {
    emit ui_->pushButton_4->released();
  } else if (event->key() == Qt::Key_5) {
    emit ui_->pushButton_5->released();
  } else if (event->key() == Qt::Key_6) {
    emit ui_->pushButton_6->released();
  } else if (event->key() == Qt::Key_7) {
    emit ui_->pushButton_7->released();
  } else if (event->key() == Qt::Key_8) {
    emit ui_->pushButton_8->released();
  } else if (event->key() == Qt::Key_9) {
    emit ui_->pushButton_9->released();
  } else if (event->key() == Qt::Key_Plus) {
    emit ui_->pushButton_Plus->released();
  } else if (event->key() == Qt::Key_Minus) {
    emit ui_->pushButton_Minus->released();
  } else if (event->key() == Qt::Key_Slash) {
    emit ui_->pushButton_Div->released();
  } else if (event->key() == Qt::Key_Asterisk) {
    emit ui_->pushButton_Mul->released();
  } else if (event->key() == Qt::Key_Period) {
    emit ui_->pushButton_Dot->released();
  } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Equal) {
    emit ui_->pushButton_Eq->released();
  } else if (event->key() == Qt::Key_Delete ||
             event->key() == Qt::Key_Backspace) {
    emit ui_->pushButton_AC->released();
  }
}

void s21::MainWindow::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui_->Result_2->text().endsWith("+") ||
      ui_->Result_2->text().endsWith("-") ||
      ui_->Result_2->text().endsWith("*") ||
      ui_->Result_2->text().endsWith("/") ||
      ui_->Result_2->text().endsWith("d") ||
      ui_->Result_2->text().endsWith("(") || ui_->Result_2->text().isEmpty() ||
      ui_->Result_2->text().endsWith("^")) {
    if (!(ui_->Result_2->text().endsWith("X"))) {
      ui_->Result->setText(ui_->Result->text() + button->text());
    }
  }
}

void s21::MainWindow::Operations() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "+/-" && !ui_->Result->text().isEmpty()) {
    if (ui_->Result->text().contains('-')) {
      ui_->Result->setText(ui_->Result->text().replace("-", ""));
    } else {
      ui_->Result->setText(ui_->Result->text().insert(0, "-"));
    }
  }
}

void s21::MainWindow::Functions() {
  QPushButton *button = (QPushButton *)sender();
  ui_->Result_2->setText(ui_->Result_2->text() + button->text() + "(");
}

void s21::MainWindow::MathOperations() {
  QPushButton *button = (QPushButton *)sender();
  if ((ui_->Result_2->text().endsWith("-") ||
       ui_->Result_2->text().endsWith("+") ||
       ui_->Result_2->text().endsWith("*") ||
       ui_->Result_2->text().endsWith("/")) &&
      ui_->Result->text() == "") {
    QString str = ui_->Result_2->text();
    str.chop(1);
    ui_->Result_2->setText(str + button->text());
  } else if (ui_->Result_2->text().endsWith("d") && ui_->Result->text() == "") {
    QString str = ui_->Result_2->text();
    str.chop(3);
    ui_->Result_2->setText(str + button->text());
  } else if (ui_->Result_2->text().endsWith("^")) {
  } else {
    ui_->Result_2->setText(ui_->Result_2->text() + ui_->Result->text());
    ui_->Result_2->setText(ui_->Result_2->text() + button->text());
    ui_->Result->setText("");
  }
}

void s21::MainWindow::PlotInit() {
  ui_->customPlot->xAxis->setLabel("x");
  ui_->customPlot->yAxis->setLabel("y");
  ui_->customPlot->xAxis2->setVisible(true);
  ui_->customPlot->xAxis2->setTickLabels(false);
  ui_->customPlot->yAxis2->setVisible(true);
  ui_->customPlot->yAxis2->setTickLabels(false);
  ui_->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  ui_->customPlot->xAxis->setRange(-10, 10);
  ui_->customPlot->yAxis->setRange(-10, 10);
}

void s21::MainWindow::OnPushButtonDotReleased() {
  if (!(ui_->Result->text().contains('.')) && !(ui_->Result->text().isEmpty()))
    ui_->Result->setText(ui_->Result->text() + ".");
}

void s21::MainWindow::OnPushButtonAcReleased() {
  ui_->Result_2->setText("");
  ui_->Result->setText("");
}

void s21::MainWindow::OnPushButtonEqReleased() {
  ui_->Result_2->setText(ui_->Result_2->text() + ui_->Result->text());
  auto result = controller_->Result(ui_->Result_2->text().toStdString(),
                                    ui_->doubleSpinBox_x->text().toDouble());
  ui_->Result_2->setText(ui_->Result_2->text() + "=");
  if (result.first) {
    // std::cout << result.second << std::endl;    // for debug
    ui_->Result->setText(QString::number(result.second, 'g', 16));
  } else {
    ui_->Result->setText("");
    ui_->Result_2->setText("Error!");
  }
}

void s21::MainWindow::OnPushButtonLeftReleased() {
  QPushButton *button = (QPushButton *)sender();
  ui_->Result_2->setText(ui_->Result_2->text() + button->text());
}

void s21::MainWindow::OnPushButtonRightReleased() {
  QPushButton *button = (QPushButton *)sender();
  ui_->Result_2->setText(ui_->Result_2->text() + ui_->Result->text() +
                         button->text());
  ui_->Result->setText("");
}

void s21::MainWindow::OnPushButtonDegreeReleased() {
  QPushButton *button = (QPushButton *)sender();
  ui_->Result_2->setText(ui_->Result_2->text() + ui_->Result->text() +
                         button->text());
  ui_->Result->setText("");
}

void s21::MainWindow::OnPushButtonXReleased() {
  QPushButton *button = (QPushButton *)sender();
  if ((ui_->Result_2->text().endsWith("(") ||
       ui_->Result_2->text().endsWith("+") ||
       ui_->Result_2->text().endsWith("-") ||
       ui_->Result_2->text().endsWith("*") ||
       ui_->Result_2->text().endsWith("/") ||
       ui_->Result_2->text().endsWith("d") ||
       ui_->Result_2->text().endsWith("^") ||
       ui_->Result_2->text().isEmpty()) &&
      ui_->Result->text().isEmpty()) {
    ui_->Result_2->setText(ui_->Result_2->text() + button->text());
  }
}

void s21::MainWindow::OnPushButtonEReleased() {
  QPushButton *button = (QPushButton *)sender();
  if (!ui_->Result->text().contains('e')) {
    if (ui_->Result->text().endsWith("1") ||
        ui_->Result->text().endsWith("2") ||
        ui_->Result->text().endsWith("3") ||
        ui_->Result->text().endsWith("4") ||
        ui_->Result->text().endsWith("5") ||
        ui_->Result->text().endsWith("6") ||
        ui_->Result->text().endsWith("7") ||
        ui_->Result->text().endsWith("8") ||
        ui_->Result->text().endsWith("9") || ui_->Result->text().endsWith("0"))
      ui_->Result->setText(ui_->Result->text() + button->text());
  }
}

void s21::MainWindow::OnRadioButtonGraphToggled(bool checked) {
  if (checked) {
    setFixedSize(865, 610);
  } else {
    setFixedSize(430, 610);
  }
}

void s21::MainWindow::OnPushButtonGraphReleased() {
  ui_->Result_2->setText(ui_->Result_2->text() + ui_->Result->text());
  ui_->Result->setText("");
  if (!controller_->Graph(ui_->Result_2->text().toStdString(),
                          ui_->doubleSpinBox_step->value(),
                          ui_->doubleSpinBox_x_left->value(),
                          ui_->doubleSpinBox_x_right->value(),
                          ui_->doubleSpinBox_y_left->value(),
                          ui_->doubleSpinBox_y_right->value())) {
    ui_->Result_2->setText("Graph Error!");
    ui_->customPlot->clearGraphs();
  } else {
    ui_->customPlot->clearGraphs();
    ui_->customPlot->addGraph();
    QVector<double> x =
        QVector<double>(controller_->GetX().begin(), controller_->GetX().end());
    QVector<double> y =
        QVector<double>(controller_->GetY().begin(), controller_->GetY().end());
    ui_->customPlot->graph(0)->setData(x, y);
    ui_->customPlot->xAxis->rescale();
    ui_->customPlot->yAxis->rescale();
    if (ui_->comboBox_style->currentIndex() == 0) {
    } else {
      ui_->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui_->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    }
  }
  ui_->customPlot->replot();
}

void s21::MainWindow::OnPushButtonCreditReleased() {
  credit_window_->show();
  this->close();
}
