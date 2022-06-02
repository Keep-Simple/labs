#include "widget.h"

#include <QFile>
#include <QGridLayout>
#include <QTextStream>
#include <random>

void Widget::on_output() {
  array.values.clear();
  for (auto i = 0; i < 10; i++) array.push(*new Vector2D());

  this->results_output->setMarkdown(
      QString("### Array of Vector2D:\n\n"
              "* Biggest Vector2D x=%1 y=%2\n"
              "* Vector2D sum (resulting vector length)=%3\n")
          .arg(QString::number(array.find_max().x))
          .arg(QString::number(array.find_max().y))
          .arg(QString::number(array.sum().calc_length())));
  print_array();
}

void Widget::on_sort_asc() {
  array.sort_asc();
  print_array();
}

void Widget::on_sort_desc() {
  array.sort_desc();
  print_array();
}

void Widget::print_array() {
  std::string array_as_string;
  for (auto v : array.values) array_as_string += v.to_string();
  this->array_output->setText(QString::fromStdString(array_as_string));
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->output_btn = new QPushButton("Start");
  this->sort_asc_btn = new QPushButton("Sort asc");
  this->sort_desc_btn = new QPushButton("Sort desc");

  this->array_output = new QTextEdit;
  this->array_output->setReadOnly(true);
  this->results_output = new QTextEdit;
  this->results_output->setReadOnly(true);

  main_layout->addWidget(this->array_output, 0, 0);
  main_layout->addWidget(this->output_btn, 0, 1);
  main_layout->addWidget(this->results_output, 0, 2);
  main_layout->addWidget(this->sort_asc_btn, 1, 0);
  main_layout->addWidget(this->sort_desc_btn, 1, 2);

  connect(this->output_btn, &QPushButton::released, this, &Widget::on_output);
  connect(this->sort_asc_btn, &QPushButton::released, this,
          &Widget::on_sort_asc);
  connect(this->sort_desc_btn, &QPushButton::released, this,
          &Widget::on_sort_desc);

  setLayout(main_layout);
}
