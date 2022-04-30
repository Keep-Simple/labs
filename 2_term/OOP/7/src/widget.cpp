#include "widget.h"

#include <QGridLayout>

void Widget::onQueueClear() {
  this->dq->erase();

  emit valueChanged(this->dq);
}

void Widget::onFrontItemInsert() {
  this->newQueueItemInput >> *this->dq;

  emit valueChanged(this->dq);
};

void Widget::onRearItemInsert() {
  *this->dq >> this->newQueueItemInput;

  emit valueChanged(this->dq);
};

void Widget::onFrontItemDelete() {
  this->dq->deleteFront();

  emit valueChanged(this->dq);
}

void Widget::onRearItemDelete() {
  this->dq->deleteRear();

  emit valueChanged(this->dq);
}

void Widget::onValueChange(CustomDeque *dq) {
  this->newQueueItemInput->clear();

  this->biggestValueInput->setText(QString::number(dq->getMaxValue()));
  this->smallestValueInput->setText(QString::number(dq->getMinValue()));
  this->averageValueInput->setText(QString::number(dq->getMinValue()));

  this->listWidget >> *dq;
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;
  QGridLayout *queueControlButtonsLayout = new QGridLayout;

  QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);

  this->dq = new CustomDeque;
  this->listWidget = new QListWidget;

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

  QLabel *frontLabel = new QLabel(QString("Front").toUpper());
  frontLabel->setAlignment(Qt::AlignLeft);

  QLabel *rearLabel = new QLabel(QString("Rear").toUpper());
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

  connect(this->insertFrontItemButton, &QPushButton::released, this,
          &Widget::onFrontItemInsert);

  connect(this->insertRearItemButton, &QPushButton::released, this,
          &Widget::onRearItemInsert);

  connect(this->deleteFrontItemButton, &QPushButton::released, this,
          &Widget::onFrontItemDelete);

  connect(this->deleteRearItemButton, &QPushButton::released, this,
          &Widget::onRearItemDelete);

  connect(this->clearQueueButton, &QPushButton::released, this,
          &Widget::onQueueClear);

  connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}
