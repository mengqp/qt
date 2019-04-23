/**
 *   \file widget.h
 *   \brief 实现柱状图要显示的widget
 *
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Histogram : public QWidget
{
public:
    Histogram(QWidget *p = NULL );
    virtual ~Histogram();
};



#endif /* WIDGET_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
