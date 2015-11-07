#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <LGraphicsView.h>
#include <QVector>

class LPianoPlain : public LGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);

signals:

public slots:

protected:
	int keyHeight;

	QGraphicsScene* scene;

	QVector<QGraphicsRectItem*> pianoStrips;

};

#endif // LPIANOPLAIN_H
