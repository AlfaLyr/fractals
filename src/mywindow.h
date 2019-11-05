/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
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
    const int DEFAULT_ITER = 300;
    const int ITER_RANGE[2] {1, 100000};
    const int NAV_BUTTON_SIZE = 26;
    const double DEFAULT_DX = 0.8 * (double)WIDTH;
    const double DEFAULT_DY = 0.;
    const double DEFAULT_ZOOM = 0.35 * (double)WIDTH;
    const double MOVE_STEP = 20.;
    const double ZOOM_STEP = 0.1;
};

#endif //MYWINDOW_H
