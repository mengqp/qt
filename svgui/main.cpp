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

	// w.setFixedSize( 400, 480 );

	w.setScaleSize( 800 );
    w.show();
	w.setLine(0, 0, 10);
	w.setLine(0, 1, 30);
	w.setLine(0, 2, 45);

	w.setLine(1, 0, 60);
	w.setLine(1, 1, 75);
	w.setLine(1, 2, 90);

    // w.showFullScreen();

    return a.exec();
}
