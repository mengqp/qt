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

    setColor(PHASE_A, Qt::darkYellow);
    setColor(PHASE_B, Qt::darkGreen);
    setColor(PHASE_C, Qt::darkRed);

    m_penWidthU = 2;
    m_penWidthI = 4;

    update();
    return true;
}

void Svgui::destroy(void)
{
    if (NULL != m_renderer) {
        delete m_renderer;
        m_renderer = NULL;
    }
}

void Svgui::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_renderer->render(&painter);

    drawMark(&painter);
    // QSize size = m_renderer->defaultSize();

    painter.end();
}

void Svgui::setColor(int index, QColor color)
{
    if (index >= PHASE_SIZE || index < 0) {
        return;
    }

    m_color[index] = color;
}

void Svgui::drawMark(QPainter *pPainter)
{
    int width = this->width();
    int height = this->height();
    // printf("height=%d width=%d\n", height, width);

    m_markUXb = width / 240 * 20;
    m_markUXe = width / 240 * 40;
    m_markIXb = width / 240 * 65;
    m_markIXe = width / 240 * 85;
    m_markY[PHASE_A] = height / 480 * 30;
    m_markY[PHASE_B] = height / 480 * 65;
    m_markY[PHASE_C] = height / 480 * 100;

    QPen pen = pPainter->pen();

	for (int i = 0; i < PHASE_SIZE; i++) {
		pen.setColor(m_color[i]);

		// U
		pen.setWidth(m_penWidthU);
		pPainter->setPen(pen);
		pPainter->drawLine(m_markUXb, m_markY[i], m_markUXe, m_markY[i]);

		// I
		pen.setWidth(m_penWidthI);
		pPainter->setPen(pen);
		pPainter->drawLine(m_markIXb, m_markY[i], m_markIXe, m_markY[i]);
    }
}
