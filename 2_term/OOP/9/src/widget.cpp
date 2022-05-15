#include "widget.h"

#include <QFile>
#include <QGridLayout>
#include <QTextStream>

#include "array.h"

void Widget::on_output() {
  const int count = 5;

  Array<double> *arrays[count];

  for (auto i = 0; i < count; i++) {
    if (i % 2) {
      arrays[i] = new BasicArray<double>();
    } else {
      arrays[i] = new SinglyLinkedArray<double>();
    }
  }

  this->class_names_output->setMarkdown(
      QString("### Basic Array:\n\n"
              "* %1\n"
              "* %2")
          .arg(QString::fromStdString(arrays[1]->get_info()))
          .arg(QString::fromStdString(arrays[1]->get_info_abstract())));

  this->results_output->setMarkdown(
      QString("### SinglyLinkedArray\n"
              "* %1\n"
              "* %2")
          .arg(QString::fromStdString(arrays[0]->get_info()))
          .arg(QString::fromStdString(arrays[0]->get_info_abstract())));
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->output_btn = new QPushButton("Print output");

  this->class_names_output = new QTextEdit;
  this->class_names_output->setReadOnly(true);

  this->results_output = new QTextEdit;
  this->results_output->setReadOnly(true);

  main_layout->addWidget(this->class_names_output, 0, 0);
  main_layout->addWidget(this->output_btn, 0, 1);
  main_layout->addWidget(this->results_output, 0, 2);

  connect(this->output_btn, &QPushButton::released, this, &Widget::on_output);

  setLayout(main_layout);
}
