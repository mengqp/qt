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

// 三相电编号
enum PHASE_INDEX{
	PHASE_A = 0,
	PHASE_B,
	PHASE_C,
	PHASE_INDEX_SIZE,
};

// 三相电类型
enum PHASE_TYPE{
	PHASE_U = 0,
	PHASE_I,
	PHASE_TYPE_SIZE,
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
	// 通过角度设置 三相线
	void setLine( int type, int index, double angle );
	// 按比例设置窗口大小
	void setScaleSize( int width );

private:
	// 画提示的ABC 标注说明
	void drawMark( QPainter *pPainter );

	// 窗口改变大小时
	void sizeChange( void );
	// 画线条
	void drawLines( QPainter *pPainter );

private:
	QSvgRenderer *m_renderer;
	QColor m_color[PHASE_INDEX_SIZE];
	int m_markY[PHASE_INDEX_SIZE];
	int m_markXb[PHASE_TYPE_SIZE];
	int m_markXe[PHASE_TYPE_SIZE];
	int m_penWidth[PHASE_TYPE_SIZE];

	QSize m_sizeOld;

	QLine m_line[PHASE_TYPE_SIZE][PHASE_INDEX_SIZE];
	double m_angle[PHASE_TYPE_SIZE][PHASE_INDEX_SIZE];

};

#endif /* SVGUI_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
