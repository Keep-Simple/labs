#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "uimatrix.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);

  // private slots:
  //  void onFrontItemInsert();
  //  void onRearItemInsert();
  //  void onFrontItemDelete();
  //  void onRearItemDelete();
  //  void onQueueClear();
  //  void onValueChange(UIMatrix *);

  // signals:
  //  void valueChanged(UIMatrix *);

 private:
  UIMatrix *matrix;

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
