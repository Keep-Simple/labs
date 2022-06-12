#pragma once

#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QWidget>
#include <stack>

#include "vyraz.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);

 private slots:
  void on_calculate();
  void on_set();

 private:
  QPushButton *start_btn;
  QPushButton *set_btn;
  QTableWidget *coff_table;
  QTextEdit *n_input;
  QTextEdit *m_input;
  QTextEdit *k_input;
  QTextEdit *x_input;
  QTextEdit *value_output;

  Vyraz *vyraz;
};
