/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#include <QApplication>
#include "mywindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWindow myWindow;

    myWindow.setWindowTitle("Fractal");
    myWindow.show();

    return app.exec();
}
