#ifndef LGRAPHICSPIANOSTRIPITEM_H
#define LGRAPHICSPIANOSTRIPITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QBrush>

class LGraphicsPianoStripItem : public QGraphicsItem
{
public:
	LGraphicsPianoStripItem();
	void paint( QPainter *painter,
		      const QStyleOptionGraphicsItem *option,
		      QWidget *widget );
	QRectF boundingRect() const;
	void setGeometry(int x, int y, int w, int h);
	void setBlackKey(bool blackKey);
	void setBackgroundColor(QColor color);
	void setbottomLineColor(QColor color);

protected:
	QPainterPath itemGeometry;
	QRect itemRect;
	QBrush paintBrush;
	bool isBlackKey;

	QColor backgroundColor;
	QColor bottomLineColor;
};

#endif // LGRAPHICSPIANOSTRIPITEM_H
