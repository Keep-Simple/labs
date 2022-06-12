#pragma once

#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QWidget>
#include <stack>

class Vyraz {
 public:
  std::vector<double> coff_n;
  std::vector<double> coff_m;
  std::vector<double> coff_k;

  double calculate(double);
};
