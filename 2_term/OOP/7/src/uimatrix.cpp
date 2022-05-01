#include "uimatrix.h"

UIMatrix::UIMatrix(unsigned _rows, unsigned _cols, const double &_initial) {
  this->mtrx = new Matrix<double>(_rows, _cols, _initial);
}

UIMatrix::~UIMatrix() { delete this->mtrx; }

void operator>>(QTableWidget *in, UIMatrix &matrix) {
  auto mtrx = matrix.mtrx;
  for (auto i = 0; i < mtrx->rows; i++)
    for (auto j = 0; j < mtrx->cols; j++) {
      (*mtrx)(i, j) = in->item(i, j)->text().toDouble();
    }
}

void operator<<(QTableWidget *out, UIMatrix &matrix) {
  auto mtrx = matrix.mtrx;
  for (auto i = 0; i < mtrx->rows; i++)
    for (auto j = 0; j < mtrx->cols; j++) {
      out->setItem(i, j, new QTableWidgetItem(QString::number((*mtrx)(i, j))));
    }
}

double UIMatrix::get_max_negative() {
  auto mtrx = (*this->mtrx);
  auto val = mtrx(0, 0);

  for (auto i = 0; i < mtrx.rows; i++)
    for (auto j = 0; j < mtrx.cols; j++) {
      val = std::min(val, mtrx(i, j));
    }

  return val;
}

double UIMatrix::get_min_positive() {
  auto mtrx = (*this->mtrx);
  auto val = mtrx(0, 0);

  for (auto i = 0; i < mtrx.rows; i++)
    for (auto j = 0; j < mtrx.cols; j++) {
      if (mtrx(i, j) > 0) val = std::min(val, mtrx(i, j));
    }

  return val;
}

double UIMatrix::get_abs_max() {
  auto mtrx = (*this->mtrx);
  auto val = mtrx(0, 0);

  for (auto i = 0; i < mtrx.rows; i++)
    for (auto j = 0; j < mtrx.cols; j++) {
      val = std::max(val, mtrx(i, j), [](double a, double b) {
        return std::abs(a) < std::abs(b);
      });
    }

  return val;
}
