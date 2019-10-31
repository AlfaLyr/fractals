/************************************************
 * Fractals
 * 
 * Author: Erica
 * 
 * License: GNU General Public License Usage
 ************************************************/

#include <complex>
#include <cmath>
#include "fractal.h"

Fractal::Fractal(QImage* img, QLabel* imageArea) : img(img), imageArea(imageArea) {}

int Fractal::mandelbrot(int x, int y)
{
    std::complex<double> z = 0;
    std::complex<double> c(double(x-dx)/zoom, double(y-dy)/zoom);

    int iterations = 0;

    while(iterations < MAX_ITERATIONS)
    {
        z = z * z + c;

        if(abs(z) > 2.) break;

        iterations++;
    }
    return iterations;
}

void Fractal::fillImage(int dx, int dy, int zoom)
{
    this->dx = dx;
    this->dy = dy;
    this->zoom = zoom;

    uint r, g, b;

    for (int x = 0; x < img->width(); x++)
    {
        for (int y = 0; y < img->height(); y++)
        {
            int iterations = mandelbrot(x-img->width()/2, y-img->height()/2);
            
            if (iterations != MAX_ITERATIONS)
            {
                r = 256*iterations*iterations/1000 * std::sin(2.*3.14159*iterations);
                g = 256*iterations*iterations/1000 * std::cos(2.*3.14159*iterations);
                b = 256*iterations*iterations/1000;
            }
            else
            {
                r= 0;
                g = 0;
                b = 0;
            }
            img->setPixel(x, y, qRgb(r, g, b));
        }
    }

    imageArea->setPixmap(QPixmap::fromImage(*img));
}
