#include "widget.h"

#include <QFile>
#include <QGridLayout>
#include <QTextStream>

#include "deposit.h"

void Widget::on_output() {
  auto terminate_date = 60 * 60 * 24 * 30 * 3;
  auto monthly_rate = .01;
  auto initial_amount = 10000;

  SimpleBankDeposit d1(0, terminate_date, monthly_rate, initial_amount);
  ComplexBankDeposit d2(0, terminate_date, monthly_rate, initial_amount);
  VIPBankDeposit d3(0, terminate_date, monthly_rate, initial_amount);

  d3.add_money(1000000);

  this->class_names_output->setMarkdown(
      QString("### BankDeposit classes:\n\n"
              "* %1\n"
              "* %2\n"
              "* %3")
          .arg(QString::fromStdString(d1.print_class_name()))
          .arg(QString::fromStdString(d2.print_class_name()))
          .arg(QString::fromStdString(d3.print_class_name())));

  auto output_string =
      QString(
          "### Results\n"
          "`monthly rate = %4, initial amount = %5, months = %6`:\n"
          "* Simple Deposit income: %1\n"
          "* Complex Deposit income: %2\n"
          "* VIP Deposit income: %3")
          .arg(QString::number(d1.calculate_income()))
          .arg(QString::number(d2.calculate_income()))
          .arg(QString::number(d3.calculate_income()))
          .arg(QString::number(monthly_rate))
          .arg(QString::number(initial_amount))
          .arg(QString::number(terminate_date / (60 * 60 * 24 * 30)));

  QFile file("Results.md");
  if (file.open(QIODevice::Append)) {
    QTextStream stream(&file);
    stream << output_string << Qt::endl << Qt::endl;
    file.close();
  }
  this->results_output->setMarkdown(output_string);
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
