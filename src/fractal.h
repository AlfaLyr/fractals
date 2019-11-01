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
    double dx, dy;
    double zoom;
    QImage* img;
    QLabel* imageArea;

public:
    const int MAX_ITERATIONS = 100;

public:
    Fractal(QImage* img, QLabel* imageArea);

    int mandelbrot(int x, int y);
    void fillImage(int dx, int dy, int zoom);
    int getDx () {return dx;}
    int getDy () {return dy;}
    double getZoom () {return zoom;}
    void zoomInOut (double);
    void shiftX (double);
    void shiftY (double);
};

#endif //FRACTAL_H
