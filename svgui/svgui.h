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

// 三相电
enum THREE_PHASE{
	PHASE_A = 0,
	PHASE_B,
	PHASE_C,
	PHASE_SIZE
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

public:
	// 设置ABC 三相顔色
	void setColor( int index, QColor color );

private:
	// 画提示的ABC 标注说明
	void drawMark( QPainter *pPainter );

private:
	QSvgRenderer *m_renderer;
	QColor m_color[PHASE_SIZE];
	int m_markY[PHASE_SIZE];

	int m_penWidthU;
	int m_penWidthI;

	int m_markUXb;
	int m_markUXe;
	int m_markIXb;
	int m_markIXe;


};

#endif /* SVGUI_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
