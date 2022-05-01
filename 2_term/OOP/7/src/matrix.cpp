#ifndef __QS_MATRIX_CPP
#define __QS_MATRIX_CPP

#include "matrix.h"

template <typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) {
  mat.resize(_rows);
  for (unsigned i = 0; i < mat.size(); i++) {
    mat[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
  mat = rhs.mat;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

template <typename T>
Matrix<T>::~Matrix() {}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
  if (&rhs == this) return *this;

  auto new_rows = rhs.get_rows();
  auto new_cols = rhs.get_cols();

  mat.resize(new_rows);
  for (auto i = 0; i < mat.size(); i++) mat[i].resize(new_cols);

  for (auto i = 0; i < new_rows; i++)
    for (auto j = 0; j < new_cols; j++) mat[i][j] = rhs(i, j);

  rows = new_rows;
  cols = new_cols;

  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
  Matrix result(rows, cols, 0.0);

  for (auto i = 0; i < rows; i++)
    for (auto j = 0; j < cols; j++) result(i, j) = this->mat[i][j] + rhs(i, j);

  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
  Matrix result(rows, cols, 0.0);

  for (auto i = 0; i < rows; i++)
    for (auto j = 0; j < cols; j++) result(i, j) = this->mat[i][j] - rhs(i, j);

  return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator++() {
  for (auto i = 0; i < rows; i++) this->mat[i][i]++;
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
  auto rows = rhs.get_rows();
  auto cols = rhs.get_cols();
  if (this->cols != rows) throw "Cannot multiply matrices";

  Matrix result(this->rows, cols, 0.0);

  for (auto i = 0; i < this->rows; i++)
    for (auto j = 0; j < cols; j++)
      for (auto k = 0; k < rows; k++)
        result(i, j) += this->mat[i][k] * rhs(k, j);

  return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() {
  Matrix result(rows, cols, 0.0);

  for (auto i = 0; i < rows; i++)
    for (auto j = 0; j < cols; j++) result(i, j) = this->mat[j][i];

  return result;
}

template <typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
  return this->mat[row][col];
}

template <typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
  return this->mat[row][col];
}

template <typename T>
unsigned Matrix<T>::get_rows() const {
  return this->rows;
}

template <typename T>
unsigned Matrix<T>::get_cols() const {
  return this->cols;
}

#endif
