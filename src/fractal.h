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
    int dx, dy;
    double zoom;
    QImage* img;
    QLabel* imageArea;

public:
    const int MAX_ITERATIONS = 1000;

public:
    Fractal(QImage* img, QLabel* imageArea);

    int mandelbrot(int x, int y);
    void fillImage(int dx, int dy, int zoom);
};

#endif //FRACTAL_H
