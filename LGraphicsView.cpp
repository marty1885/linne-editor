#include "LGraphicsView.h"

LGraphicsView::LGraphicsView(QWidget *parent) :
	QGraphicsView(parent)
{
	translateVec = QVector2D(0,0);
}

void LGraphicsView::translate(qreal dx, qreal dy)
{
	translateVec += QVector2D(dx,dy);
	setSceneRect(translateVec.x(),translateVec.y(),width(),height());
}

void LGraphicsView::translateTo(qreal x, qreal y)
{
	translateVec = QVector2D(x,y);
	setSceneRect(translateVec.x(),translateVec.y(),width(),height());
}
