#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "uimatrix.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);

 private slots:
  void on_substract();
  void on_add();
  void on_multiply();
  void on_transpose();
  void on_value_change();

 signals:
  void value_changed();

 private:
  UIMatrix *matrix_a;
  UIMatrix *matrix_b;
  UIMatrix *matrix_res;

  QTableWidget *ui_matrix_a;
  QTableWidget *ui_matrix_b;
  QTableWidget *ui_matrix_res;

  QPushButton *add_matrices_btn;
  QPushButton *substract_matrices_btn;
  QPushButton *multiply_matrices_btn;
  QPushButton *transpose_matrix_btn;

  QLineEdit *max_negative_input;
  QLineEdit *min_positive_input;
  QLineEdit *max_abs_input;

  void sync_with_table();
  void sync_with_model();
};
