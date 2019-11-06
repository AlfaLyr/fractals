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

#include <iostream>

Fractal::Fractal(QImage* img, QLabel* imageArea, double dx, double dy, double zoom, int maxIterations, int hueStart, int hueEnd) :
    img(img), imageArea(imageArea), dx(dx), dy(dy), zoom(zoom), maxIterations(maxIterations), hueStart(hueStart), hueEnd(hueEnd) {}

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
        if (zrsqr + zisqr > 25.) return (double)it + 1. - log(log(sqrt(zrsqr + zisqr))) / log(2.);
    }

    return -1.;
}

void Fractal::fillImage()
{
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

            double cColourFactor = pow(colourFactor, 4);

            int hue;
            int hueDif = int(hueStart - hueEnd);
            if (abs(int(hueStart-hueEnd)) < 180) hue = hueEnd + cColourFactor * hueDif;
            else hue = hueEnd + cColourFactor * (360 - abs(hueDif));
            if (hue < 0) hue += 360;
            if (hue > 359) hue -= 360;

            int value = 255 * cColourFactor;
            QColor pixel = QColor::fromHsv(hue, 255, value);

            img->setPixel(x, y, qRgb(pixel.red(), pixel.green(), pixel.blue()));
        }
    }

    imageArea->setPixmap(QPixmap::fromImage(*img));
}

double Fractal::interpolate (double x1, double y1, double y2, double x)
{
    return y1 + (y2 - y1) * (x - x1);
}

void Fractal::resetZoom(double newDx, double newDy, double newZoom)
{
    dx = newDx;
    dy = newDy;
    zoom = newZoom;

    fillImage();
}

void Fractal::mouseZoom(int x1, int y1, int x2, int y2)
{
    double difx = abs(x2 - x1) / double(img->width());
    double dify = abs(y2 - y1) / double(img->height());

    double distx = abs(x1 + x2) / 2. - img->width() / 2.;
    double disty = abs(y1 + y2) / 2. - img->height() / 2.;

    dx -= distx * img->width() / zoom;
    dy -= disty * img->height() / zoom;
    zoom /= (difx + dify) / 2.;

    fillImage();
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
    dx += distance / zoom;
    fillImage();
}

void Fractal::shiftY(double distance)
{
    dy += distance / zoom;
    fillImage();
}

void Fractal::setHues(int newHueStart, int newHueEnd)
{
    hueStart = newHueStart;
    hueEnd = newHueEnd;
    fillImage();
}
