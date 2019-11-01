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
#include <map>
#include <string>
#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    imageArea = new QLabel;

    std::map<std::string, QPushButton*> navButtons;
    navButtons["dxp"] = new QPushButton("🡒");
    navButtons["dxm"] = new QPushButton("🡐");
    navButtons["dyp"] = new QPushButton("🡑");
    navButtons["dym"] = new QPushButton("🡓");
    navButtons["zoomIn"] = new QPushButton("+");
    navButtons["zoomOut"] = new QPushButton("-");

    for(const auto& button : navButtons)
    {
        button.second->setFixedSize(30, 30);
    }

    QPushButton* saveButton = new QPushButton("Save image");

    img = new QImage(WIDTH, HEIGHT, QImage::Format_RGB888);
    Fractal* fractal = new Fractal(img, imageArea);
    fractal->fillImage(0.7*WIDTH, 0, 0.4*WIDTH);

    QVBoxLayout* vBox = new QVBoxLayout(this);
    QHBoxLayout* hBox = new QHBoxLayout();

    QGridLayout* nav = new QGridLayout;
    nav->addWidget(navButtons["dyp"], 0, 1);
    nav->addWidget(navButtons["dxm"], 1, 0);
    nav->addWidget(navButtons["dxp"], 1, 2);
    nav->addWidget(navButtons["dym"], 2, 1);

    hBox->addLayout(nav, Qt::AlignLeft);
    hBox->addStretch(100);
    hBox->addWidget(navButtons["zoomIn"], 1, Qt::AlignRight);
    hBox->addWidget(navButtons["zoomOut"], 1, Qt::AlignRight);
    vBox->addWidget(imageArea, 1 , Qt::AlignCenter);
    vBox->addLayout(hBox);
    vBox->addWidget(saveButton, 1, Qt::AlignRight);
    
    connect(saveButton, &QPushButton::clicked, this, &MyWindow::saveImage);
    connect(navButtons["zoomIn"], &QPushButton::clicked, [=](){fractal->zoomInOut(1.1);});
    connect(navButtons["zoomOut"], &QPushButton::clicked, [=](){fractal->zoomInOut(0.9);});
    connect(navButtons["dxp"], &QPushButton::clicked, [=](){fractal->shiftX(20.*double(WIDTH)/fractal->getZoom());});
    connect(navButtons["dxm"], &QPushButton::clicked, [=](){fractal->shiftX(-20.*double(WIDTH)/fractal->getZoom());});
    connect(navButtons["dyp"], &QPushButton::clicked, [=](){fractal->shiftY(-20.*double(HEIGHT)/fractal->getZoom());});
    connect(navButtons["dym"], &QPushButton::clicked, [=](){fractal->shiftY(20.*double(HEIGHT)/fractal->getZoom());});
}

void MyWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"));
    img->save(fileName);
}
