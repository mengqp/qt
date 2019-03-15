#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include "../../cc/sinewave/src/sinewave.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	radius = 0;
	sinewave_get_a_circle( 0 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPen pen;
    //1、画字
    QPainter painter(this);
	double x, y;
	double tmp_x, tmp_y;

	//8、画多个点
    QPointF pointf[180];
    pen.setWidth(1);
    painter.setPen(pen); // 设置画笔
    for (int i = 0; i < 180; ++i) {
		sinewave_get_circle(i, &x, &y);
		tmp_x = x * radius * 5 + 10;
		tmp_y = y * radius * 2 + 240;
		// printf( "radius=%d tmp_x=%f tmp_y=%f \n", radius, tmp_x, tmp_y );
		pointf[i].setX( tmp_x);
        pointf[i].setY( tmp_y);
    }
    painter.drawPoints(pointf, 180);

	painter.end();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
	radius = value;
	update();
	// printf("value=%d\n", value);
}
