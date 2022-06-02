#pragma once

#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "array.cpp"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  Array<Vector2D> array;
  void print_array();

 private slots:
  void on_output();
  void on_sort_asc();
  void on_sort_desc();

 private:
  QPushButton *output_btn;
  QPushButton *sort_asc_btn;
  QPushButton *sort_desc_btn;

  QTextEdit *array_output;
  QTextEdit *results_output;
};
