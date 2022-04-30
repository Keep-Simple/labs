#include "widget.h"

#include <QGridLayout>
#include <QMessageBox>

void TriangleWidget::onInputConfirm() {
  TriangleSides sides;
  sides.a = this->side_a->text().toDouble();
  sides.b = this->side_b->text().toDouble();
  sides.c = this->side_c->text().toDouble();
  this->triangle = new Triangle(sides);

  emit valueChanged(this->triangle);
}

void TriangleWidget::onInputIncrease() {
  this->triangle->increaseSidesBy(this->increaseSidesBy->text().toDouble());

  emit valueChanged(this->triangle);
}

void TriangleWidget::onValueChange(Triangle *triangle) {
  auto sides = triangle->getSides();
  auto heights = triangle->getHeights();
  auto angles = triangle->getAngles();

  this->side_a->setText(QString::number(sides.a));
  this->side_b->setText(QString::number(sides.b));
  this->side_c->setText(QString::number(sides.c));

  this->area->setText(QString::number(triangle->getArea()));
  this->perimeter->setText(QString::number(triangle->getPerimeter()));
  this->isRectangular->setText(QVariant(triangle->isRight()).toString());

  this->heights->setMarkdown(QString("### Triangle Heights:\n\n"
                                     "*	AK: %1\n"
                                     "* BK: %2\n"
                                     "* CK: %3")
                                 .arg(heights.ak)
                                 .arg(heights.bk)
                                 .arg(heights.ck));

  this->angles->setMarkdown(QString("### Triangle Angles:\n\n"
                                    "* ABC: %1\n"
                                    "* BCA: %2\n"
                                    "* CAB: %3")
                                .arg(angles.abc)
                                .arg(angles.bca)
                                .arg(angles.cab));
}

TriangleWidget::TriangleWidget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;

  this->triangle = nullptr;

  this->side_a = new QLineEdit("3");
  this->side_a->setPlaceholderText("Side A");

  this->side_b = new QLineEdit("4");
  this->side_b->setPlaceholderText("Side B");

  this->side_c = new QLineEdit("5");
  this->side_c->setPlaceholderText("Side C");

  this->increaseSidesBy = new QLineEdit("1");

  this->isRectangular = new QLineEdit;
  this->isRectangular->setReadOnly(true);

  this->area = new QLineEdit;
  this->area->setReadOnly(true);

  this->perimeter = new QLineEdit;
  this->perimeter->setReadOnly(true);

  this->angles = new QTextEdit();
  this->angles->setReadOnly(true);

  this->heights = new QTextEdit();
  this->heights->setReadOnly(true);

  this->confirmInput = new QPushButton("Calculate");
  this->confirmIncrease = new QPushButton("+ To each side");

  mainLayout->addWidget(this->side_a, 0, 0);
  mainLayout->addWidget(this->side_b, 0, 1);
  mainLayout->addWidget(this->side_c, 0, 2);
  mainLayout->addWidget(this->confirmInput, 0, 3);

  mainLayout->addWidget(this->increaseSidesBy, 1, 0);
  mainLayout->addWidget(this->confirmIncrease, 1, 1);

  mainLayout->addWidget(new QLabel("Is right triangle:"), 3, 0);
  mainLayout->addWidget(this->isRectangular, 3, 1);

  mainLayout->addWidget(new QLabel("Area:"), 4, 0);
  mainLayout->addWidget(this->area, 4, 1);

  mainLayout->addWidget(new QLabel("Perimeter:"), 5, 0);
  mainLayout->addWidget(this->perimeter, 5, 1);

  mainLayout->addWidget(this->angles, 6, 0);
  mainLayout->addWidget(this->heights, 6, 1);

  connect(this->confirmInput, &QPushButton::released, this,
          &TriangleWidget::onInputConfirm);

  connect(this->confirmIncrease, &QPushButton::released, this,
          &TriangleWidget::onInputIncrease);

  connect(this, &TriangleWidget::valueChanged, &TriangleWidget::onValueChange);

  setLayout(mainLayout);

  this->onInputConfirm();
}
