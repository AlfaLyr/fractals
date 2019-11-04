/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#ifndef FRACTAL_H
#define FRACTAL_H

#include <QLabel>

class Fractal
{
private:
    QImage* img;
    QLabel* imageArea;
    double dx, dy;
    double zoom;
    int maxIterations;

private slots:
    double interpolate (double, double, double, double);

public:
    Fractal(QImage*, QLabel*, double, double, double, int);

    double mandelbrot(double, double);
    void fillImage();
    int getDx () {return dx;}
    int getDy () {return dy;}
    double getZoom () {return zoom;}
    void newMaxIter(int);
    void zoomInOut (double);
    void shiftX (double);
    void shiftY (double);
};

#endif //FRACTAL_H
