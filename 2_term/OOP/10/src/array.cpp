#ifndef __ARRAY_H
#define __ARRAY_H

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <string>
#include <vector>

template <class T>
class Array {
 public:
  std::vector<T> values;

  void sort_asc() {
    sort_desc();
    std::reverse(values.begin(), values.end());
  }
  void sort_desc() { std::sort(values.begin(), values.end()); }
  T sum() { return std::reduce(values.begin(), values.end()); }
  T find_max() { return *std::max_element(values.begin(), values.end()); }
  void push(T const &v) { values.push_back(v); }
};

class Vector2D {
 public:
  double x, y;

  Vector2D() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, 100);
    x = distr(eng);
    y = distr(eng);
  }

  Vector2D operator+(const Vector2D &v) {
    Vector2D temp;
    temp.x = x + v.x;
    temp.y = y + v.y;
    return temp;
  }

  double calc_length() const { return std::sqrt(x * x + y * y); }

  bool operator<(const Vector2D &v) const {
    return calc_length() < v.calc_length();
  }

  bool operator>(const Vector2D &v) const { return *this > v; }

  std::string to_string() const {
    return "x=" + std::to_string(x) + " y=" + std::to_string(y) +
           " length=" + std::to_string(calc_length()) + "\n";
  }
};

#endif
