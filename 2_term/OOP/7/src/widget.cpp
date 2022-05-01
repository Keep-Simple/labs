#include "widget.h"

#include <QGridLayout>
#include <iostream>

// void Widget::onQueueClear() {
//   this->dq->erase();

//   emit valueChanged(this->dq);
// }

// void Widget::onFrontItemInsert() {
//   this->newQueueItemInput >> *this->dq;

//   emit valueChanged(this->dq);
// };

// void Widget::onRearItemInsert() {
//   *this->dq >> this->newQueueItemInput;

//   emit valueChanged(this->dq);
// };

// void Widget::onFrontItemDelete() {
//   this->dq->deleteFront();

//   emit valueChanged(this->dq);
// }

// void Widget::onRearItemDelete() {
//   this->dq->deleteRear();

//   emit valueChanged(this->dq);
// }

// void Widget::onValueChange(UIMatrix *matrix) {
// this->newQueueItemInput->clear();

// this->biggestValueInput->setText(QString::number(dq->getMaxValue()));
// this->smallestValueInput->setText(QString::number(dq->getMinValue()));
// this->averageValueInput->setText(QString::number(dq->getMinValue()));

// this->listWidget >> *matrix;
// }

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *mainLayout = new QGridLayout;
  auto *queueControlButtonsLayout = new QGridLayout;

  QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);

  this->matrix = new UIMatrix(10, 10, 1.0);
  this->listWidget = new QListWidget;
  UIMatrix mat1(10, 10, 1.0);
  UIMatrix mat2(10, 10, 2.0);

  mat1(0, 0) = 10;
  mat1(1, 0) = 90;
  mat1(0, 2) = 0.1;
  mat1(3, 3) = -10;
  mat1(3, 3) = -100;

  std::cout << mat1.get_abs_max() << std::endl;
  std::cout << mat1.get_max_negative() << std::endl;
  std::cout << mat1.get_min_positive() << std::endl;

  auto mat3 = mat1 + mat2;

  for (auto i = 0; i < mat3.get_rows(); i++) {
    for (auto j = 0; j < mat3.get_cols(); j++) {
      std::cout << mat3(i, j) << ", ";
    }
    std::cout << std::endl;
  }

  this->insertFrontItemButton = new QPushButton("Insert");
  this->insertRearItemButton = new QPushButton("Insert");
  this->deleteFrontItemButton = new QPushButton("Delete");
  this->deleteRearItemButton = new QPushButton("Delete");

  this->clearQueueButton = new QPushButton("Clear queue");
  this->clearQueueButton->setSizePolicy(sizePolicy);

  this->newQueueItemInput = new QLineEdit;
  this->smallestValueInput = new QLineEdit;
  this->biggestValueInput = new QLineEdit;
  this->averageValueInput = new QLineEdit;

  auto frontLabel = new QLabel(QString("Front").toUpper());
  frontLabel->setAlignment(Qt::AlignLeft);

  auto rearLabel = new QLabel(QString("Rear").toUpper());
  rearLabel->setAlignment(Qt::AlignRight);

  smallestValueInput->setDisabled(true);
  biggestValueInput->setDisabled(true);
  averageValueInput->setDisabled(true);

  queueControlButtonsLayout->addWidget(frontLabel, 0, 0);
  queueControlButtonsLayout->addWidget(this->insertFrontItemButton, 1, 0);
  queueControlButtonsLayout->addWidget(this->deleteFrontItemButton, 2, 0);

  queueControlButtonsLayout->addWidget(this->clearQueueButton, 1, 1, 2, 1);

  queueControlButtonsLayout->addWidget(rearLabel, 0, 2);
  queueControlButtonsLayout->addWidget(this->insertRearItemButton, 1, 2);
  queueControlButtonsLayout->addWidget(this->deleteRearItemButton, 2, 2);

  mainLayout->addWidget(this->listWidget, 0, 0, 1, 2);
  mainLayout->addWidget(this->newQueueItemInput, 1, 0, 1, 2);
  mainLayout->addLayout(queueControlButtonsLayout, 2, 0, 1, 2);

  mainLayout->addWidget(new QLabel("Biggest value:"), 3, 0);
  mainLayout->addWidget(this->biggestValueInput, 3, 1);

  mainLayout->addWidget(new QLabel("Minimum value:"), 4, 0);
  mainLayout->addWidget(this->smallestValueInput, 4, 1);

  mainLayout->addWidget(new QLabel("Average value:"), 5, 0);
  mainLayout->addWidget(this->averageValueInput, 5, 1);

  // connect(this->insertFrontItemButton, &QPushButton::released, this,
  //         &Widget::onFrontItemInsert);

  // connect(this->insertRearItemButton, &QPushButton::released, this,
  //         &Widget::onRearItemInsert);

  // connect(this->deleteFrontItemButton, &QPushButton::released, this,
  //         &Widget::onFrontItemDelete);

  // connect(this->deleteRearItemButton, &QPushButton::released, this,
  //         &Widget::onRearItemDelete);

  // connect(this->clearQueueButton, &QPushButton::released, this,
  //         &Widget::onQueueClear);

  // connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}
