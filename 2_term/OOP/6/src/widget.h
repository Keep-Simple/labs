#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "polynom.h"

class PolynomWidget : public QWidget {
  Q_OBJECT

 public:
  PolynomWidget(QWidget *parent = nullptr);

 private slots:
  void onInputConfirm();
  void onConfirmInvertCoff();
  void onConfirmAdd();
  void onConfirmSubstract();
  void onInputIncreaseBy();
  void onValueChange();

 signals:
  void valueChanged();

 private:
  // read only
  QLineEdit *y_value;

  // write and read
  QLineEdit *coff_a;
  QLineEdit *coff_b;
  QLineEdit *coff_c;

  QLineEdit *coff_a2;
  QLineEdit *coff_b2;
  QLineEdit *coff_c2;

  QLineEdit *x_value;

  QPushButton *confirmInput;
  QPushButton *confirmInvertCoff;
  QPushButton *confirmAdd;
  QPushButton *confirmSubstract;

  QLineEdit *increaseBy;
  QPushButton *confirmIncreaseBy;

  Polynom *polynom;
};
