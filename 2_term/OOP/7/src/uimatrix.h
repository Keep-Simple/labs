#pragma once
#import <QLabel>
#import <QLineEdit>
#import <QListWidget>
#import <QTableWidget>

#import "matrix.h"

class UIMatrix : public Matrix<double> {
 public:
  UIMatrix(unsigned _rows, unsigned _cols, const double &_initial)
      : Matrix<double>(_rows, _cols, _initial){};
  double getMaxValue();

  double get_max_negative();
  double get_min_positive();
  double get_abs_max();

  friend void operator>>(QListWidget *, UIMatrix &);
  friend void operator<<(QListWidget *, UIMatrix &);
};
