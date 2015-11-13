#include "LGraphicsPianoStripItem.h"
#include <QPainter>
LGraphicsPianoStripItem::LGraphicsPianoStripItem(QGraphicsItem *parent) :
	QGraphicsObject(parent)
{
	paintBrush = Qt::black;
	isBlackKey = false;

	QVector<QPointF> points;
	points.push_back(QPointF(0,0));
	points.push_back(QPointF(83,0));
	points.push_back(QPointF(83,13));
	points.push_back(QPointF(0,13));
	itemGeometry.addPolygon(QPolygonF(points));
	itemRect = QRect(0,0,83,13);

	backgroundColor = Qt::black;
	bottomLineColor = Qt::black;
}

void LGraphicsPianoStripItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->fillPath(itemGeometry,backgroundColor);
	//painter->fillPath(itemGeometry,QColor::fromHsv(0,0,217));

	painter->setPen(QPen(bottomLineColor,1,Qt::SolidLine));
	QLine line(itemRect.x(),itemRect.y()+itemRect.height()-1,itemRect.x()+itemRect.width()-1,itemRect.y()+itemRect.height()-1);
	painter->drawLine(line);
}

QRectF LGraphicsPianoStripItem::boundingRect() const
{
	return itemGeometry.boundingRect();
}

void LGraphicsPianoStripItem::setGeometry(int x, int y, int w, int h)
{
	itemGeometry = QPainterPath();
	QVector<QPointF> points;
	points.push_back(QPointF(x,y));
	points.push_back(QPointF(x+w,y));
	points.push_back(QPointF(x+w,y+h));
	points.push_back(QPointF(x,y+h));
	itemGeometry.addPolygon(QPolygonF(points));
	itemRect = QRect(x,y,w,h);
}

void LGraphicsPianoStripItem::setBlackKey(bool blackKey)
{
	isBlackKey = blackKey;
	this->update();
}

void LGraphicsPianoStripItem::setBackgroundColor(QColor color)
{
	backgroundColor = color;
}

void LGraphicsPianoStripItem::setbottomLineColor(QColor color)
{
	bottomLineColor = color;
}
