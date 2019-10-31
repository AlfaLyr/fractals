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
#include "fractal.h"

class MyWindow : public QWidget
{    
public:
    MyWindow(QWidget *parent = 0);

private slots:
    void saveImage();
    int mandelbrot(double, double);

private:
    QImage* img;
    QLabel* imageArea;
    const int WIDTH = 500;
    const int HEIGHT = 500;
};

#endif //MYWINDOW_H
