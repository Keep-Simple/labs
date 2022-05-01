#include "widget.h"

#include <QGridLayout>
#include <iostream>

void Widget::on_add() {
  this->sync_with_table();
  *this->matrix_res->mtrx = (*this->matrix_a->mtrx + *this->matrix_b->mtrx);
  emit value_changed();
}

void Widget::on_multiply() {
  this->sync_with_table();
  *this->matrix_res->mtrx = (*this->matrix_a->mtrx * *this->matrix_b->mtrx);
  emit value_changed();
}

void Widget::on_substract() {
  this->sync_with_table();
  *this->matrix_res->mtrx = (*this->matrix_a->mtrx - *this->matrix_b->mtrx);
  emit value_changed();
}

void Widget::on_transpose() {
  this->sync_with_table();
  *this->matrix_res->mtrx = this->matrix_res->mtrx->transpose();
  emit value_changed();
}

void Widget::sync_with_table() {
  this->ui_matrix_a >> *this->matrix_a;
  this->ui_matrix_b >> *this->matrix_b;
  this->ui_matrix_res >> *this->matrix_res;
}

void Widget::sync_with_model() {
  this->ui_matrix_a << *this->matrix_a;
  this->ui_matrix_b << *this->matrix_b;
  this->ui_matrix_res << *this->matrix_res;
}

void Widget::on_value_change() {
  auto matrix = this->matrix_res;
  this->max_abs_input->setText(QString::number(matrix->get_abs_max()));
  this->max_negative_input->setText(
      QString::number(matrix->get_max_negative()));
  this->min_positive_input->setText(
      QString::number(matrix->get_min_positive()));

  this->sync_with_model();
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *mainLayout = new QGridLayout;
  auto *btns_layout = new QGridLayout;

  this->matrix_a = new UIMatrix(10, 10, 1.0);
  this->matrix_b = new UIMatrix(10, 10, 2.0);
  this->matrix_res = new UIMatrix(10, 10, 0.0);
  this->ui_matrix_a = new QTableWidget(10, 10);
  this->ui_matrix_b = new QTableWidget(10, 10);
  this->ui_matrix_res = new QTableWidget(10, 10);

  this->add_matrices_btn = new QPushButton("Add");
  this->substract_matrices_btn = new QPushButton("Substract");
  this->multiply_matrices_btn = new QPushButton("Multiply");
  this->transpose_matrix_btn = new QPushButton("Transpose");

  this->min_positive_input = new QLineEdit;
  this->max_negative_input = new QLineEdit;
  this->max_abs_input = new QLineEdit;
  min_positive_input->setReadOnly(true);
  max_negative_input->setReadOnly(true);
  max_abs_input->setReadOnly(true);

  btns_layout->addWidget(this->add_matrices_btn, 0, 0);
  btns_layout->addWidget(this->substract_matrices_btn, 1, 0);

  btns_layout->addWidget(this->multiply_matrices_btn, 0, 2);
  btns_layout->addWidget(this->transpose_matrix_btn, 1, 2);

  mainLayout->addWidget(this->ui_matrix_a, 0, 0, 1, 1);
  mainLayout->addWidget(this->ui_matrix_b, 0, 1, 1, 1);
  mainLayout->addLayout(btns_layout, 1, 0, 1, 2);
  mainLayout->addWidget(this->ui_matrix_res, 2, 0, 1, 2);

  mainLayout->addWidget(new QLabel("Max negative:"), 3, 0);
  mainLayout->addWidget(this->max_negative_input, 3, 1);

  mainLayout->addWidget(new QLabel("Min postive:"), 4, 0);
  mainLayout->addWidget(this->min_positive_input, 4, 1);

  mainLayout->addWidget(new QLabel("Max abs:"), 5, 0);
  mainLayout->addWidget(this->max_abs_input, 5, 1);

  connect(this->add_matrices_btn, &QPushButton::released, this,
          &Widget::on_add);
  connect(this->substract_matrices_btn, &QPushButton::released, this,
          &Widget::on_substract);
  connect(this->multiply_matrices_btn, &QPushButton::released, this,
          &Widget::on_multiply);
  connect(this->transpose_matrix_btn, &QPushButton::released, this,
          &Widget::on_transpose);

  connect(this, &Widget::value_changed, &Widget::on_value_change);

  setLayout(mainLayout);

  this->sync_with_model();
}
