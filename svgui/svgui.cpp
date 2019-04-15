#include "svgui.h"
#include <QPainter>

Svgui::Svgui(QWidget *p) : QSvgWidget(p)
{
	m_renderer = NULL;
	printf("%s\n", __FUNCTION__);

	init();
}

Svgui::~Svgui(void)
{
	printf("%s\n", __FUNCTION__);
	destroy();
}

bool Svgui::init(void)
{
	m_renderer = new QSvgRenderer(QString("ui.svg"), this);

	setColor(COLOR_A, Qt::darkYellow);
	setColor(COLOR_A, Qt::darkGreen);
	setColor(COLOR_A, Qt::darkRed);

	update();
	return true;
}

void Svgui::destroy(void)
{
	if ( NULL != m_renderer ) {
		delete m_renderer;
		m_renderer = NULL;
	}

}

void Svgui::paintEvent( QPaintEvent *)
{
	QPainter painter( this );
	m_renderer->render( &painter );
	QSize size = m_renderer->defaultSize();
	int width = size.width();
	int height = size.height();
	// printf("height=%d width=%d\n", height, width);

	QPen pen = painter.pen();
	pen.setColor( m_color[COLOR_A]);
	pen.setWidth( 4 );
	painter.setPen( pen );

	painter.drawLine(width/240 * 30, height/480 * 30, width/240 * 70, height/480 * 30 );


	painter.end();
}

void Svgui::setColor(int index, QColor color )
{
	if ( index >= COLOR_SIZE || index < 0) {
		return;
	}

	m_color[index] = color;
}
