#include "widget.h"

#include <QFile>
#include <QGridLayout>
#include <QTextStream>
#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

template <typename T>
std::string to_str(std::vector<T> &vec) {
  std::ostringstream oss;
  if (!vec.empty()) {
    std::copy(vec.begin(), vec.end() - 1,
              std::ostream_iterator<int>(oss, ", "));
    oss << vec.back();
  }
  return oss.str();
}

double get_random_double() {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 100);
  return distr(eng);
}

struct filterDoubles {
  bool operator()(const double x) { return x < 50; }
};

void Widget::on_start() {
  stack.empty();
  vector.clear();
  vector2.clear();

  for (auto i = 0; i < 10; i++) {
    vector.push_back(get_random_double());
    vector2.push_back(get_random_double());
  }
  this->output_1->setMarkdown(
      QString("### Vector1:\n%1").arg(QString::fromStdString(to_str(vector))));

  vector.erase(vector.begin() + 2, vector.begin() + 7);
  vector.at(3) = 999;
  vector.insert(vector.end(), vector2.begin(), vector2.end());
  std::sort(vector.begin(), vector.end(), std::greater<double>());
  auto find_res = std::find_if(vector.begin(), vector.end(), filterDoubles());

  this->output_2->setMarkdown(QString("### Vector1 sorted desc:\n%1"
                                      "\n### Vector2:\n%2"
                                      "\n### Find result:\n%3")
                                  .arg(QString::fromStdString(to_str(vector)))
                                  .arg(QString::fromStdString(to_str(vector2)))
                                  .arg(QString::number(*find_res))

  );

  std::for_each(vector.begin(), vector.end(), [this](double x) {
    if (filterDoubles()(x)) {
      stack.push(x);
    }
  });

  std::vector<double> vector_from_stack;
  while (stack.size()) {
    vector_from_stack.push_back(stack.top());
    stack.pop();
  }
  std::sort(vector.begin(), vector.end());
  std::sort(vector_from_stack.begin(), vector_from_stack.end());

  this->output_3->setMarkdown(
      QString("### Vector1 sorted asc:\n%1"
              "\n### Stack1 sorted asc:\n%2")
          .arg(QString::fromStdString(to_str(vector)))
          .arg(QString::fromStdString(to_str(vector_from_stack))));

  std::vector<double> merged_vector(vector.size() + vector_from_stack.size());
  std::merge(vector.begin(), vector.end(), vector_from_stack.begin(),
             vector_from_stack.end(), merged_vector.begin());

  int count = std::count_if(merged_vector.begin(), merged_vector.end(),
                            filterDoubles());
  this->output_4->setMarkdown(
      QString("### Merged vector:\n%1"
              "\n### %2 elements satisfy filter")
          .arg(QString::fromStdString(to_str(merged_vector)))
          .arg(QString::number(count)));
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->start_btn = new QPushButton("Start");

  this->output_1 = new QTextEdit;
  this->output_2 = new QTextEdit;
  this->output_3 = new QTextEdit;
  this->output_4 = new QTextEdit;

  main_layout->addWidget(this->output_1, 0, 0);
  main_layout->addWidget(this->output_2, 0, 1);
  main_layout->addWidget(this->output_3, 1, 0);
  main_layout->addWidget(this->output_4, 1, 1);
  main_layout->addWidget(this->start_btn, 2, 0);

  connect(this->start_btn, &QPushButton::released, this, &Widget::on_start);

  setLayout(main_layout);
}
