#include <QPainter>
#include <math.h>

#include "svgui.h"

#define PI 3.14159265259

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
    this->setGeometry(0, 0, 400, 480);

    m_renderer = new QSvgRenderer(QString("ui.svg"), this);

    setColor(PHASE_A, Qt::darkYellow);
    setColor(PHASE_B, Qt::darkGreen);
    setColor(PHASE_C, Qt::darkRed);

    m_penWidth[PHASE_U] = 2;
    m_penWidth[PHASE_I] = 4;

    m_sizeOld.setWidth(this->width());
    m_sizeOld.setHeight(this->height());

    for (int i = 0; i < PHASE_TYPE_SIZE; i++) {
        for (int j = 0; j < PHASE_INDEX_SIZE; j++) {
            m_line[i][j].setLine(0, 0, 0, 0);
        }
    }

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
    drawLines(&painter);

    painter.end();
}

void Svgui::setColor(int index, QColor color)
{
    if (index >= PHASE_INDEX_SIZE || index < 0) {
        return;
    }

    m_color[index] = color;

    update();
}

void Svgui::drawMark(QPainter *pPainter)
{
    int width = this->width();
    int height = this->height();
    // printf("height=%d width=%d\n", height, width);

    m_markXb[PHASE_U] = width * 20 / 240 ;
    m_markXe[PHASE_U] = width * 40 / 240 ;
    m_markXb[PHASE_I] = width * 60 / 240 ;
    m_markXe[PHASE_I] = width * 80/ 240 ;
    m_markY[PHASE_A] = height * 20/ 480 ;
    m_markY[PHASE_B] = height * 40/ 480 ;
    m_markY[PHASE_C] = height * 60/ 480 ;

    QPen pen = pPainter->pen();

    for (int j = 0; j < PHASE_TYPE_SIZE; j++) {
        for (int i = 0; i < PHASE_INDEX_SIZE; i++) {
            pen.setColor(m_color[i]);

            // U
            pen.setWidth(m_penWidth[j]);
            pPainter->setPen(pen);
            pPainter->drawLine(m_markXb[j], m_markY[i], m_markXe[j],
                               m_markY[i]);
        }
    }
}

void Svgui::setLine(int type, int index, double angle)
{
    int width = this->width();
    int height = this->height();

    int radius = width * 9 / 20;
    QPoint center;
    center.setX(width / 2);
    center.setY(width / 2 + height - width);
    double real_angle = angle;

    if (type > PHASE_TYPE_SIZE || index > PHASE_INDEX_SIZE) {
        return;
    }

    // 求角度
    while (real_angle < 0 || real_angle >= 360) {
        if (real_angle < 0) {
            real_angle += 360;
        }
        else {
            real_angle -= 360;
        }
    }
    double angle_step = real_angle * (PI / 180);

    int x = radius * cos(angle_step);
    int y = radius * sin(angle_step);

    m_line[type][index].setLine(center.x() + x, center.y() - y, center.x() - x,
                                center.y() + y);

	m_angle[type][index] = angle;

    update();
}

void Svgui::drawLines(QPainter *pPainter)
{
    sizeChange();

    QPen pen = pPainter->pen();
    for (int i = 0; i < PHASE_TYPE_SIZE; i++) {
        for (int j = 0; j < PHASE_INDEX_SIZE; j++) {
            if (m_line[i][j].p1().x() == 0 && m_line[i][j].p1().y() == 0) {
                continue;
            }
            printf("%d %d %d %d\n", m_line[i][j].p1().x(),
                   m_line[i][j].p1().y(), m_line[i][j].p2().x(),
                   m_line[i][j].p2().y());
            pen.setWidth(m_penWidth[i]);
            pen.setColor(m_color[j]);
            pPainter->setPen(pen);
            pPainter->drawLine(m_line[i][j].p1().x(), m_line[i][j].p1().y(),
                               m_line[i][j].p2().x(), m_line[i][j].p2().y());
        }
    }
}

void Svgui::sizeChange(void)
{
    if (this->size() == m_sizeOld)
        return;

    for (int i = 0; i < PHASE_TYPE_SIZE; i++) {
        for (int j = 0; j < PHASE_INDEX_SIZE; j++) {
			setLine(i, j, m_angle[i][j]);
        }
    }

	m_sizeOld = this->size();
}

void Svgui::setScaleSize(int width )
{
	this->setFixedSize( width, width * 480 / 400 );
	update();
}
