#import "deque.h"

#import <QLabel>
#import <QLineEdit>
#import <QListWidget>
#import <QTableWidget>

class CustomDeque : public Deque {
public:
  const double getMaxValue();
  const double getMinValue();
  const double averageValue();

  void operator=(const CustomDeque &);

  friend void operator>>(QListWidget *, CustomDeque &);
  friend void operator<<(QListWidget *, CustomDeque &);
  friend void operator>>(QLineEdit *, CustomDeque &);
  friend void operator>>(CustomDeque &, QLineEdit *);
  friend void operator+(double, CustomDeque &);
  friend void operator+(CustomDeque &, double);
  friend void operator-(CustomDeque &, Node *);
  friend void operator-(Node *, CustomDeque &);
};
