#ifndef LGRAPHICSVIEW_H
#define LGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QVector2D>

class LGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit LGraphicsView(QWidget *parent = 0);

	void translate(qreal dx, qreal dy);
	void setTranslation(qreal x, qreal y);

signals:

public slots:


protected:
	QVector2D translateVec;

};

#endif // LGRAPHICSVIEW_H
