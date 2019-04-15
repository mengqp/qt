/**
 *   \file svgui.h
 *   \brief 三相电压和电流的矢量图
 *
 *  svg 为矢量图，ui 指的是三相的电压和电流。
 *
 */

#ifndef SVGUI_H
#define SVGUI_H

#include <QSvgWidget>
#include <QWidget>
#include <QSvgRenderer>
#include <QColor>

enum COLORABC{
	COLOR_A = 0,
	COLOR_B,
	COLOR_C,
	COLOR_SIZE
};

class Svgui : public QSvgWidget {
public:
    Svgui(QWidget *p = 0);
    virtual ~Svgui(void);

private:
	// 初始化
	bool init();
	// 退出
	void destroy(void);

public:
	void paintEvent( QPaintEvent *);

private:
	// 设置ABC 三相顔色
	void setColor( int index, QColor color );

private:
	QSvgRenderer *m_renderer;
	QColor m_color[COLOR_SIZE];


};

#endif /* SVGUI_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
