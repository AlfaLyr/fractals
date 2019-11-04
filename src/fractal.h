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
    uint hueStart, hueEnd;

private slots:
    double interpolate (double, double, double, double);
    double mandelbrot(double, double);

public:
    Fractal(QImage*, QLabel*, double, double, double, int, int, int);

    void fillImage();
    void resetZoom(double, double, double);
    void mouseZoom(int, int, int, int);
    void newMaxIter(int);
    void zoomInOut (double);
    void shiftX (double);
    void shiftY (double);
    void setHues (int, int);
};

#endif //FRACTAL_H
