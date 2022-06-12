#include "vyraz.h"

#include "cmath"
#include "numeric"

double Vyraz::calculate(double x) {
  if (x < 0) throw "Sqrt of number less then 0";
  if (x >= 100) throw "Log10 of number less or equal than 0";
  if (x == 10) throw "Division by 0";

  return (std::accumulate(coff_n.begin(), coff_n.end(), 0) * sqrt(x)) +
         (std::accumulate(coff_m.begin(), coff_m.end(), 0) * log10(100 - x)) +
         (std::accumulate(coff_k.begin(), coff_k.end(), 0) / (x - 10));
}
