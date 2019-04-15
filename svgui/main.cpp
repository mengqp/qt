/**
 *   \file main.cpp
 *   \brief 测试画svg 图像
 *
 */

#include <QApplication>
#include "svgui.h"

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    Svgui w;
    w.showFullScreen();
    //w.show();

    return a.exec();
}
