#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QGridLayout>
#include <QMessageBox>
#include <QTextStream>
#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

double get_random_double() {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 100);
  return distr(eng);
}

void Widget::on_set() {
  auto n = this->n_input->toPlainText().toInt();
  auto m = this->m_input->toPlainText().toInt();
  auto k = this->k_input->toPlainText().toInt();
  this->vyraz->coff_n.resize(n);
  this->vyraz->coff_m.resize(m);
  this->vyraz->coff_k.resize(k);
  this->coff_table->setRowCount(3);
  this->coff_table->setColumnCount(std::max({n, m, k}));

  for (auto i = 0; i < this->coff_table->rowCount(); i++)
    for (auto j = 0; j < this->coff_table->columnCount(); j++)
      this->coff_table->setItem(
          i, j, new QTableWidgetItem(QString::number(get_random_double())));
}

void Widget::on_calculate() {
  try {
    std::vector<double>* temp;
    for (auto i = 0; i < this->coff_table->rowCount(); i++) {
      switch (i) {
        case 0:
          temp = &this->vyraz->coff_n;
          break;
        case 1:
          temp = &this->vyraz->coff_m;
          break;
        case 2:
          temp = &this->vyraz->coff_k;
          break;
      }
      for (auto j = 0; j < this->coff_table->columnCount(); j++) {
        if (temp->size() < j + 1) throw "Out of bounds assignment";

        (*temp)[j] = this->coff_table->item(i, j)->text().toDouble();
      }
    }
    bool ok;
    auto x = this->x_input->toPlainText().toDouble(&ok);
    if (!ok) throw "X should be a number";

    this->value_output->setText(QString::number(this->vyraz->calculate(x)));
  } catch (const char* e) {
    QMessageBox error;
    error.setText(QString(e));
    error.exec();
  } catch (...) {
    QMessageBox error;
    error.setText(QString::fromStdString("Unknown Error :("));
    error.exec();
  }
}

Widget::Widget(QWidget* parent) : QWidget(parent) {
  this->vyraz = new Vyraz;
  auto main_layout = new QGridLayout;
  this->start_btn = new QPushButton("Calculate");
  this->set_btn = new QPushButton("Set");
  this->n_input = new QTextEdit("3");
  this->m_input = new QTextEdit("3");
  this->k_input = new QTextEdit("3");
  this->x_input = new QTextEdit("11");
  this->value_output = new QTextEdit;
  this->value_output->setReadOnly(true);
  this->coff_table = new QTableWidget;

  main_layout->addWidget(this->n_input, 0, 0);
  main_layout->addWidget(this->m_input, 0, 1);
  main_layout->addWidget(this->k_input, 0, 2);
  main_layout->addWidget(this->x_input, 0, 3);
  main_layout->addWidget(this->set_btn, 1, 0);
  main_layout->addWidget(this->coff_table, 2, 0, 2, 4);
  main_layout->addWidget(this->start_btn, 4, 0);
  main_layout->addWidget(this->value_output, 4, 2);

  connect(this->start_btn, &QPushButton::released, this, &Widget::on_calculate);
  connect(this->set_btn, &QPushButton::released, this, &Widget::on_set);

  setLayout(main_layout);
}
