#import "uimatrix.h"

void operator>>(QListWidget *in, UIMatrix &matrix) {
  // for (auto i = 0; i < in->count(); i++) {
  //   in->setCurrentRow(i);
  //   matrix + in->currentItem()->text().toDouble();
  // }
}

void operator<<(QListWidget *out, UIMatrix &matrix) {
  out->clear();

  // for (Node *temp = dq.getFront(); temp != nullptr; temp = temp->next) {
  //   out->addItem(QString::number(temp->data));
  // }
}

double UIMatrix::get_max_negative() {
  double val = (*this)(0, 0);
  for (auto i = 0; i < this->rows; i++)
    for (auto j = 0; j < this->cols; j++) {
      val = std::min(val, (*this)(i, j));
    }

  return val;
}

double UIMatrix::get_min_positive() {
  double val = (*this)(0, 0);
  for (auto i = 0; i < this->rows; i++)
    for (auto j = 0; j < this->cols; j++) {
      if ((*this)(i, j) > 0) val = std::min(val, (*this)(i, j));
    }

  return val;
}

double UIMatrix::get_abs_max() {
  double val = (*this)(0, 0);
  for (auto i = 0; i < this->rows; i++)
    for (auto j = 0; j < this->cols; j++) {
      val = std::max(val, (*this)(i, j), [](double a, double b) {
        return std::abs(a) < std::abs(b);
      });
    }

  return val;
}
