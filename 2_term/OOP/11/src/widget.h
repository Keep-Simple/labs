#pragma once

#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <stack>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  void print_array();

  std::stack<double> stack;
  std::vector<double> vector;
  std::vector<double> vector2;
 private slots:
  void on_start();

 private:
  QPushButton *start_btn;
  QTextEdit *output_1;
  QTextEdit *output_2;
  QTextEdit *output_3;
  QTextEdit *output_4;
};
