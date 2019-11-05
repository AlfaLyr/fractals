/************************************************
 * Fractals
 *
 * Author: Erica
 *
 * License: GNU General Public License Usage
 ************************************************/

#include <map>
#include <string>
#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    imageArea = new QLabel;

    std::map<std::string, QPushButton*> navButtons;
    navButtons["dxp"] = new QPushButton("🡒");
    navButtons["dxm"] = new QPushButton("🡐");
    navButtons["dyp"] = new QPushButton("🡑");
    navButtons["dym"] = new QPushButton("🡓");
    navButtons["zoomIn"] = new QPushButton("+");
    navButtons["zoomOut"] = new QPushButton("-");

    for(const auto& button : navButtons)
    {
        button.second->setFixedSize(NAV_BUTTON_SIZE, NAV_BUTTON_SIZE);
        button.second->setAutoRepeat(true);
    }

    QPushButton* saveButton = new QPushButton("Save image");

    QPushButton* resetButton = new QPushButton("Reset");

    QSpinBox* maxIterBox = new QSpinBox;
    maxIterBox->setRange(ITER_RANGE[0], ITER_RANGE[1]);
    maxIterBox->setValue(DEFAULT_ITER);

    QComboBox* selectFractal = new QComboBox;
    selectFractal->addItem("Mandelbrot set");
    
    QSlider* hue1 = new QSlider(Qt::Horizontal);
    hue1->setMaximum(359);
    QSlider* hue2 = new QSlider(Qt::Horizontal);
    hue2->setMaximum(359);
    this->setStyleSheet(
        "QSlider::groove:horizontal {"
            "background-color:qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                "stop:0 #ff0000, "
                "stop:0.17 #ffff00, "
                "stop:0.33 #00ff00, "
                "stop:0.50 #00ffff, "
                "stop:0.67 #0000ff, "
                "stop:0.83 #ff00ff, "
                "stop:1 #ff0000);"
            "height: 10px}"
        "QSlider::handle:horizontal {"
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #000000, stop:1 #333333);"
            "width: 10px;"
            "border: 1px solid #aaaaaa}");

    img = new QImage(WIDTH, HEIGHT, QImage::Format_RGB888);

    fractal = new Fractal(img, imageArea, DEFAULT_DX, DEFAULT_DY, DEFAULT_ZOOM, maxIterBox->value(), hue1->value(), hue2->value());
    fractal->fillImage();

    QVBoxLayout* container = new QVBoxLayout(this);
    QVBoxLayout* rightControls = new QVBoxLayout;
    QHBoxLayout* controls = new QHBoxLayout;
    QHBoxLayout* zoomNav = new QHBoxLayout;
    QVBoxLayout* navControls = new QVBoxLayout;
    QGridLayout* positionNav = new QGridLayout;
    QFormLayout* options = new QFormLayout;

    positionNav->addWidget(navButtons["dyp"], 0, 1);
    positionNav->addWidget(navButtons["dxm"], 1, 0);
    positionNav->addWidget(navButtons["dxp"], 1, 2);
    positionNav->addWidget(navButtons["dym"], 2, 1);
    
    zoomNav->addWidget(navButtons["zoomOut"]);
    zoomNav->addWidget(navButtons["zoomIn"]);

    navControls->addLayout(positionNav);
    navControls->addSpacing(0.5 * navButtons["zoomOut"]->width());
    navControls->addLayout(zoomNav);
    navControls->addWidget(resetButton);
    navControls->addStretch();

    options->addRow("Fractal type:", selectFractal);
    options->addRow("Start colour:", hue1);
    options->addRow("End colour:", hue2);
    options->addRow("Max iterations:", maxIterBox);

    rightControls->addLayout(options, Qt::AlignRight);
    rightControls->addWidget(saveButton, 0, Qt::AlignRight);

    controls->addLayout(navControls);
    controls->addStretch(3);
    controls->addLayout(rightControls);
    
    container->addWidget(imageArea);
    container->addLayout(controls);

    connect(saveButton, &QPushButton::clicked, this, &MyWindow::saveImage);
    connect(resetButton, &QPushButton::clicked, [&](){fractal->resetZoom(DEFAULT_DX, DEFAULT_DY, DEFAULT_ZOOM);});
    connect(navButtons["zoomIn"], &QPushButton::clicked, [&](){fractal->zoomInOut(1. + ZOOM_STEP);});
    connect(navButtons["zoomOut"], &QPushButton::clicked, [&](){fractal->zoomInOut(1. - ZOOM_STEP);});
    connect(navButtons["dxp"], &QPushButton::clicked, [&](){fractal->shiftX(-MOVE_STEP*double(WIDTH));});
    connect(navButtons["dxm"], &QPushButton::clicked, [&](){fractal->shiftX(MOVE_STEP*double(WIDTH));});
    connect(navButtons["dyp"], &QPushButton::clicked, [&](){fractal->shiftY(MOVE_STEP*double(HEIGHT));});
    connect(navButtons["dym"], &QPushButton::clicked, [&](){fractal->shiftY(-MOVE_STEP*double(HEIGHT));});
    connect(maxIterBox, QOverload<int>::of(&QSpinBox::valueChanged), [&](int i){fractal->newMaxIter(i);});
    connect(hue1, &QSlider::valueChanged, [=](int i){fractal->setHues(i, hue2->value());});
    connect(hue2, &QSlider::valueChanged, [=](int i){fractal->setHues(hue1->value(), i);});
}

void MyWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"));
    img->save(fileName);
}

void MyWindow::mousePressEvent(QMouseEvent* event)
{
    if (imageArea->underMouse())
    {
        mousePress.setX(event->pos().rx()-imageArea->x());
        mousePress.setY(event->pos().ry()-imageArea->y());
        mouseRelease = mousePress;

        if (!zoomArea) zoomArea = new QRubberBand(QRubberBand::Rectangle, imageArea);
        zoomArea->setGeometry(QRect(mousePress, mouseRelease).normalized());
        zoomArea->show();
    }
}

void MyWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (zoomArea)
    {
        mouseRelease.setX(event->pos().rx()-imageArea->x());
        mouseRelease.setY(event->pos().ry()-imageArea->y());
        zoomArea->setGeometry(QRect(mousePress, mouseRelease).normalized());
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (zoomArea)
    {
        mouseRelease.setX(event->pos().rx()-imageArea->x());
        mouseRelease.setY(event->pos().ry()-imageArea->y());
        zoomArea->hide();

        delete zoomArea;
        zoomArea = nullptr;

        fractal->mouseZoom(mousePress.rx(), mousePress.ry(), mouseRelease.rx(), mouseRelease.ry());
    }
}

MyWindow::~MyWindow()
{
    delete fractal;
}
