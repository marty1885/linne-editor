#ifndef LGRAPHICSPIANOSTRIPITEM_H
#define LGRAPHICSPIANOSTRIPITEM_H

#include <QGraphicsObject>
#include <QBrush>

class LGraphicsPianoStripItem : public QGraphicsObject
{
	Q_OBJECT
public:
	explicit LGraphicsPianoStripItem(QGraphicsItem *parent = 0);
	void paint( QPainter *painter,
		      const QStyleOptionGraphicsItem *option,
		      QWidget *widget );
	QRectF boundingRect() const;
	void setGeometry(int x, int y, int w, int h);
	void setGeometry(QRect rect);
	void setBlackKey(bool blackKey);
	void setBackgroundColor(QColor color);
	void setbottomLineColor(QColor color);

	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

signals:
	void mouseEntered();

public slots:

protected:
	QPainterPath itemGeometry;
	QRect itemRect;
	QBrush paintBrush;
	bool isBlackKey;

	QColor backgroundColor;
	QColor bottomLineColor;

};

#endif // LGRAPHICSPIANOSTRIPITEM_H
