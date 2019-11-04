/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#include <vector>
#include <cmath>
#include "fractal.h"

Fractal::Fractal(QImage* img, QLabel* imageArea, double dx, double dy, double zoom, int maxIterations) :
    img(img), imageArea(imageArea), dx(dx), dy(dy), zoom(zoom), maxIterations(maxIterations) {}

double Fractal::mandelbrot(double cr, double ci)
{
    double zr = 0.;
    double zi = 0.;
    double zrsqr = 0.;
    double zisqr = 0.;

    for (int it = 0; it < maxIterations; it++)
    {
        zi = zr * zi;
        zi += zi;
        zi += ci;
        zr = zrsqr - zisqr + cr;
        zrsqr = pow(zr, 2);
        zisqr = pow(zi, 2);
        //if (zrsqr + zisqr > 4.) return (double)it + 1. - log(log(sqrt(zrsqr + zisqr))) / log(2.);
        if (zrsqr + zisqr > 25.) return (double)it + 1. - log(log(sqrt(zrsqr + zisqr))) / log(2.);
    }

    return -1.;
}

void Fractal::fillImage()
{
    uint h = 0, s = 255, v = 255;

    std::vector<int> histogram(maxIterations, 0);
    std::vector<std::vector<double>> vMandelbrot(img->width(), std::vector<double>(img->height(), 0.));
    std::vector<double> totalPix;
    int sumIter = 0;

    for (int x = 0; x < img->width(); x++)
    {
        for (int y = 0; y < img->height(); y++)
        {
            double scaledX = ((double)x - (double)img->width()/2.)/zoom - dx/(double)img->width();
            double scaledY = ((double)y - (double)img->height()/2.)/zoom - dy/(double)img->width();
            
            double it = mandelbrot(scaledX, scaledY);
            vMandelbrot[x][y] = it;
            (it >= 0.) ? histogram[(int)it]++ : it = 0.;
        }
    }

    for (int i=0; i < maxIterations; i++) sumIter += histogram[i];

    double tP = 0.;

    for (int i=0; i < maxIterations; i++)
    {
        tP += (double)histogram[i] / sumIter;
        totalPix.push_back(tP);
    }

    for (int x = 0; x < img->width(); x++)
    {
        for (int y = 0; y < img->height(); y++)
        {
            double colourFactor = interpolate((double)floor(vMandelbrot[x][y]), totalPix[floor(vMandelbrot[x][y])], totalPix[ceil(vMandelbrot[x][y])], vMandelbrot[x][y]);

            h = 255 * (1.-pow(colourFactor,3)) + 20;
            v = 255 * pow(colourFactor,3);
            QColor pixel = QColor::fromHsv(h, s, v);

            img->setPixel(x, y, qRgb(pixel.red(), pixel.green(), pixel.blue()));
        }
    }

    imageArea->setPixmap(QPixmap::fromImage(*img));
}

double Fractal::interpolate (double x1, double y1, double y2, double x)
{
    return y1 + (y2 - y1) * (x - x1);
}

void Fractal::newMaxIter(int newMaxIterations)
{
    maxIterations = newMaxIterations;
    fillImage();
}

void Fractal::zoomInOut(double factor)
{
    zoom *= factor;
    fillImage();
}

void Fractal::shiftX(double distance)
{
    dx += distance;
    fillImage();
}

void Fractal::shiftY(double distance)
{
    dy += distance;
    fillImage();
}
