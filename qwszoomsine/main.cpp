/**
 *   \file main.cpp
 *   \brief 利用画点得出的正弦图
 *
 */

#include "mainwindow.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.showFullScreen();
    //w.show();

    return a.exec();
}
