/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QRubberBand>
#include "fractal.h"

class MyWindow : public QWidget
{    
public:
    MyWindow(QWidget *parent = 0);
    virtual ~MyWindow();

private slots:
    void saveImage();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private:
    QImage* img;
    QLabel* imageArea;
    QRubberBand* zoomArea = nullptr;
    Fractal* fractal;
    QPoint mousePress;
    QPoint mouseRelease;
    const int WIDTH = 500;
    const int HEIGHT = 500;
};

#endif //MYWINDOW_H
