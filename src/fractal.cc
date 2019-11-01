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
    std::complex<double> c(double(x) / zoom - dx / img->width(), double(y) / zoom - dy / img->height());

    for(int it = 0; it < MAX_ITERATIONS; it++)
    {
        if (std::abs(z) > 2.) return it;
        z = z * z + c;
    }
    return 0;
}

void Fractal::fillImage(int dx, int dy, int zoom)
{
    this->dx = dx;
    this->dy = dy;
    this->zoom = zoom;

    uint r, g, b;
    
    uint r0 = 255, g0 = 255, b0 = 0;
    uint r1 = 255, g1 = 0, b1 = 255;
    uint rmix, gmix, bmix;

    for (int x = 0; x < img->width(); x++)
    {
        for (int y = 0; y < img->height(); y++)
        {
            int iterations = mandelbrot(x-img->width()/2, y-img->height()/2);
            double colourfactor = (double)iterations / MAX_ITERATIONS;

            rmix = ((double)iterations / MAX_ITERATIONS) * (double)r0 + (1. - (double)iterations / MAX_ITERATIONS) * (double)r1;
            gmix = ((double)iterations / MAX_ITERATIONS) * (double)g0 + (1. - (double)iterations / MAX_ITERATIONS) * (double)g1;
            bmix = ((double)iterations / MAX_ITERATIONS) * (double)b0 + (1. - (double)iterations / MAX_ITERATIONS) * (double)b1;
            
            r = colourfactor * rmix;
            g = colourfactor * gmix;
            b = colourfactor * bmix;

            img->setPixel(x, y, qRgb(r, g, b));
        }
    }

    imageArea->setPixmap(QPixmap::fromImage(*img));
}

void Fractal::zoomInOut(double factor)
{
    zoom *= factor;
    fillImage(dx, dy, zoom);
}

void Fractal::shiftX(double distance)
{
    dx += distance;
    fillImage(dx, dy, zoom);
}

void Fractal::shiftY(double distance)
{
    dy += distance;
    fillImage(dx, dy, zoom);
}
