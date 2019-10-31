/************************************************
 * Fractals
 * 
 * Author: Erica
 * 
 * License: GNU General Public License Usage
 ************************************************/

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <complex>
#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    imageArea = new QLabel;

    QSpinBox* dx = new QSpinBox;
    dx->setRange(-10*WIDTH, 10*WIDTH);
    dx->setValue(0.3*WIDTH);
    QSpinBox* dy = new QSpinBox;
    dy->setRange(-10*HEIGHT, 10*HEIGHT);
    dy->setValue(0);
    QSpinBox* zoom = new QSpinBox;
    zoom->setRange(0.1*WIDTH, 10*WIDTH);
    zoom->setValue(0.4*WIDTH);
    
    QPushButton* button = new QPushButton("Save image");

    img = new QImage(WIDTH, HEIGHT, QImage::Format_RGB888);
    Fractal* fractal = new Fractal(img, imageArea);
    fractal->fillImage(dx->value(), dy->value(), zoom->value());

    QVBoxLayout* vBox = new QVBoxLayout(this);
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addStretch(100);
    hBox->addWidget(dx, 0, Qt::AlignRight);
    hBox->addWidget(dy, 0, Qt::AlignRight);
    hBox->addWidget(zoom, 0, Qt::AlignRight);
    vBox->addWidget(imageArea, 1 , Qt::AlignCenter);
    vBox->addLayout(hBox);
    vBox->addWidget(button, 1, Qt::AlignRight);
    
    connect(button, &QPushButton::clicked, this, &MyWindow::saveImage);
    connect(dx, QOverload<int>::of(&QSpinBox::valueChanged), [=](int i){fractal->fillImage(i, dy->value(), zoom->value());});
    connect(dy, QOverload<int>::of(&QSpinBox::valueChanged), [=](int i){fractal->fillImage(dx->value(), i, zoom->value());});
    connect(zoom, QOverload<int>::of(&QSpinBox::valueChanged), [=](int i){fractal->fillImage(dx->value(), dy->value(), i);});
}

void MyWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"));
    img->save(fileName);
}
