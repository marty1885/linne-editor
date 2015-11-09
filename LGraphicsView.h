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

signals:

public slots:


protected:

};

#endif // LGRAPHICSVIEW_H
