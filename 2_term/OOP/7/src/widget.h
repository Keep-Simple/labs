#pragma once

#include "customdeque.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);

private slots:
  void onFrontItemInsert();
  void onRearItemInsert();
  void onFrontItemDelete();
  void onRearItemDelete();
  void onQueueClear();
  void onValueChange(CustomDeque *dq);

signals:
  void valueChanged(CustomDeque *dq);

private:
  CustomDeque *dq;

  QListWidget *listWidget;
  QLineEdit *newQueueItemInput;

  QPushButton *insertFrontItemButton;
  QPushButton *insertRearItemButton;
  QPushButton *deleteFrontItemButton;
  QPushButton *deleteRearItemButton;
  QPushButton *clearQueueButton;

  QLineEdit *biggestValueInput;
  QLineEdit *smallestValueInput;
  QLineEdit *averageValueInput;
};
