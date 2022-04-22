#include "widget.h"

#include <QGridLayout>
#include <QMessageBox>

#include "polynom.h"

void PolynomWidget::onInputConfirm() {
  QLineEdit *coffInputs[] = {this->coff_a, this->coff_b, this->coff_c};

  coffInputs >> *this->polynom;

  emit valueChanged();
}

void PolynomWidget::onInputIncreaseBy() {
  (*this->polynom) * this->increaseBy->text().toDouble();
  emit valueChanged();
}

void PolynomWidget::onConfirmSubstract() {
  QLineEdit *coffI2nputs[] = {this->coff_a2, this->coff_b2, this->coff_c2};
  Polynom substractPolynom;

  coffI2nputs >> substractPolynom;
  (*this->polynom) - substractPolynom;

  emit valueChanged();
}

void PolynomWidget::onConfirmAdd() {
  QLineEdit *coffI2nputs[] = {this->coff_a2, this->coff_b2, this->coff_c2};
  Polynom addPolynom;

  coffI2nputs >> addPolynom;
  (*this->polynom) + addPolynom;

  emit valueChanged();
}

void PolynomWidget::onConfirmInvertCoff() {
  !(*this->polynom);
  emit valueChanged();
}

void PolynomWidget::onValueChange() {
  QLineEdit *sideInputs[] = {this->coff_a, this->coff_b, this->coff_c};

  sideInputs << *this->polynom;

  this->y_value->setText(
      QString::number((*this->polynom)(this->x_value->text().toDouble())));
}

PolynomWidget::PolynomWidget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;

  this->polynom = new Polynom;

  this->coff_a = new QLineEdit("1");
  this->coff_a->setPlaceholderText("Coff A");

  this->coff_b = new QLineEdit("2");
  this->coff_b->setPlaceholderText("Coff B");

  this->coff_c = new QLineEdit("0");
  this->coff_c->setPlaceholderText("Coff C");

  this->coff_a2 = new QLineEdit;
  this->coff_a2->setPlaceholderText("Coff A2");

  this->coff_b2 = new QLineEdit;
  this->coff_b2->setPlaceholderText("Coff B2");

  this->coff_c2 = new QLineEdit;
  this->coff_c2->setPlaceholderText("Coff C2");

  this->x_value = new QLineEdit("1");

  this->increaseBy = new QLineEdit("2");

  this->y_value = new QLineEdit;
  this->y_value->setReadOnly(true);

  this->confirmInput = new QPushButton("Calculate");
  this->confirmIncreaseBy = new QPushButton("Increasy coff by");
  this->confirmInvertCoff = new QPushButton("Invert coff");
  this->confirmAdd = new QPushButton("Add polynoms");
  this->confirmSubstract = new QPushButton("Substract polynoms");

  mainLayout->addWidget(this->coff_a, 0, 0);
  mainLayout->addWidget(this->coff_b, 0, 1);
  mainLayout->addWidget(this->coff_c, 0, 2);
  mainLayout->addWidget(this->confirmInput, 0, 3);
  mainLayout->addWidget(this->confirmInvertCoff, 0, 4);

  mainLayout->addWidget(this->coff_a2, 2, 0);
  mainLayout->addWidget(this->coff_b2, 2, 1);
  mainLayout->addWidget(this->coff_c2, 2, 2);
  mainLayout->addWidget(this->confirmAdd, 2, 3);
  mainLayout->addWidget(this->confirmSubstract, 2, 4);

  mainLayout->addWidget(this->increaseBy, 4, 0);
  mainLayout->addWidget(this->confirmIncreaseBy, 4, 1);

  mainLayout->addWidget(new QLabel("Enter x value"), 5, 0);
  mainLayout->addWidget(this->x_value, 5, 1);
  mainLayout->addWidget(new QLabel("Evaluated y value"), 5, 2);
  mainLayout->addWidget(this->y_value, 5, 3);

  connect(this->confirmInput, &QPushButton::released, this,
          &PolynomWidget::onInputConfirm);

  connect(this->confirmIncreaseBy, &QPushButton::released, this,
          &PolynomWidget::onInputIncreaseBy);

  connect(this->confirmInvertCoff, &QPushButton::released, this,
          &PolynomWidget::onConfirmInvertCoff);

  connect(this->confirmSubstract, &QPushButton::released, this,
          &PolynomWidget::onConfirmSubstract);

  connect(this->confirmAdd, &QPushButton::released, this,
          &PolynomWidget::onConfirmAdd);

  connect(this, &PolynomWidget::valueChanged, &PolynomWidget::onValueChange);

  setLayout(mainLayout);

  this->onInputConfirm();
}
