#include "GLWidget.h"
#include <QApplication>
#include "transparencysliders.h"
#include <iostream>
#include <QHBoxLayout>
#include <QWidget>
#include <transfer.h>

using namespace std;


int main(int argc, char *argv[])
{
    QGLFormat glFormat = QGLFormat::defaultFormat();
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);
    glFormat.setSamples(4);
    QGLFormat::setDefaultFormat(glFormat);

    QApplication a(argc, argv);

    transparencySliders Slider;
    GLWidget w;

    Transfer Yes;
    Yes.acceptGLWidget(&w);
    Yes.show();


//     QT widget integration
    Slider.acceptGLWidget(&w);

    QWidget *window1 = new QWidget();
    QWidget *window2 = new QWidget();

    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();


    // Reducing the size of 2
    layout1->addWidget(&w);
    window1->setLayout(layout1);
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(2);
    window1->setSizePolicy(spLeft);

    layout2->addWidget(&Slider);
    window2->setLayout(layout2);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    window2->setSizePolicy(spRight);

    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *window = new QWidget();

    layout->addWidget(window1);
    layout->addWidget(window2);


    window->setLayout(layout);
    window->setMinimumSize(1100,700);
    window->show();

    return a.exec();
}


