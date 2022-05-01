#pragma once
#include <QTableWidget>

#import "matrix.h"

class UIMatrix {
 public:
  UIMatrix(unsigned _rows, unsigned _cols, const double &_initial);
  ~UIMatrix();

  Matrix<double> *mtrx;

  double get_max_negative();
  double get_min_positive();
  double get_abs_max();

  friend void operator>>(QTableWidget *, UIMatrix &);
  friend void operator<<(QTableWidget *, UIMatrix &);
};
