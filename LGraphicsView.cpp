#include "LGraphicsView.h"
#include <QDebug>
#include <QScrollBar>

LGraphicsView::LGraphicsView(QWidget *parent) :
	QGraphicsView(parent)
{
}

void LGraphicsView::translate(qreal dx, qreal dy)
{
	centerOn(dx+width()/2,dy+height()/2);
}
