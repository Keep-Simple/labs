#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "triangle.h"

class TriangleWidget : public QWidget {
  Q_OBJECT

 public:
  TriangleWidget(QWidget *parent = nullptr);

 private slots:
  void onInputConfirm();
  void onInputIncrease();
  void onValueChange(Triangle *triangle);

 signals:
  void valueChanged(Triangle *triangle);

 private:
  QLineEdit *side_a;
  QLineEdit *side_b;
  QLineEdit *side_c;
  QPushButton *confirmInput;

  QLineEdit *increaseSidesBy;
  QPushButton *confirmIncrease;

  QLineEdit *area;
  QLineEdit *perimeter;
  QLineEdit *isRectangular;
  QTextEdit *angles;
  QTextEdit *heights;

  Triangle *triangle;
};
