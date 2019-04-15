/**
 *   \file main.cpp
 *   \brief 测试画svg 图像
 *
 */

#include <QApplication>
#include "svgui.h"
// #include <unistd.h>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    Svgui w;

	w.setScaleSize( 400 );
    w.show();
	w.setLine(0, 0, 10);
	w.setLine(0, 1, 30);
	w.setLine(0, 2, 45);

	w.setLine(1, 0, 60);
	w.setLine(1, 1, 75);
	w.setLine(1, 2, 90);

    return a.exec();
}
