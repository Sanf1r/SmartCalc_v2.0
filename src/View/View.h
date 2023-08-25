#ifndef SRC_VIEW_VIEW_H
#define SRC_VIEW_VIEW_H

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <initializer_list>
#include <iostream>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class CreditWindow;
}  // namespace Ui
QT_END_NAMESPACE

namespace s21 {

class CreditWindow : public QWidget {
  Q_OBJECT
 public:
  // Default constructor
  explicit CreditWindow(Controller *c, QWidget *parent = 0);
  // Destructor
  ~CreditWindow();

 signals:
  // Signal for main window
  void BaseWindow();

 private:
  Controller *controller_;
  Ui::CreditWindow *ui_;

 private slots:
  // Method for credit calculation
  void OnPushButtonReturnReleased();
  // Method for return button
  void OnPushButtonCalcReleased();
};

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  // Default constructor
  explicit MainWindow(Controller *c, QWidget *parent = nullptr);
  // Destructor
  ~MainWindow();

 private:
  Controller *controller_;
  Ui::MainWindow *ui_;
  CreditWindow *credit_window_;

 private slots:
  // Methods for connecting buttons, init of graph and for input of string
  void keyPressEvent(QKeyEvent *event);
  void DigitsNumbers();
  void Operations();
  void Functions();
  void MathOperations();
  void PlotInit();
  void OnPushButtonDotReleased();
  void OnPushButtonAcReleased();
  void OnPushButtonEqReleased();
  void OnPushButtonLeftReleased();
  void OnPushButtonRightReleased();
  void OnPushButtonDegreeReleased();
  void OnPushButtonXReleased();
  void OnPushButtonEReleased();
  void OnRadioButtonGraphToggled(bool checked);
  void OnPushButtonGraphReleased();
  void OnPushButtonCreditReleased();
};

}  // namespace s21

#endif
