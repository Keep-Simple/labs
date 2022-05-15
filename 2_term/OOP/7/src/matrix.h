#ifndef __ARRAY_H
#define __ARRAY_H

#include <vector>

template <typename T>
class Matrix {
 public:
  Matrix(unsigned _rows, unsigned _cols, const T& _initial);
  Matrix(const Matrix<T>& rhs);
  virtual ~Matrix();

  std::vector<std::vector<T> > mat;
  unsigned rows;
  unsigned cols;

  Matrix<T>& operator=(const Matrix<T>& rhs);
  Matrix<T> operator+(const Matrix<T>& rhs);
  Matrix<T>& operator++();
  Matrix<T> operator-(const Matrix<T>& rhs);
  Matrix<T> operator*(const Matrix<T>& rhs);
  Matrix<T> transpose();

  T& operator()(const unsigned& row, const unsigned& col);
  const T& operator()(const unsigned& row, const unsigned& col) const;

  unsigned get_rows() const;
  unsigned get_cols() const;
};

#include "matrix.cpp"

#endif
