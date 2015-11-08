#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <LGraphicsView.h>
#include <QVector>

class LGraphicsPianoStripItem;

class LPianoPlain : public LGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void setKeyNum(int num);
	void setKeyOffset(int offset);
	void mouseMoveEvent(QMouseEvent* event);

signals:
	void mouseHoverChanged(int id);

public slots:

protected:
	int keyHeight;
	int keyOffset;

	QGraphicsScene* scene;
	QVector<LGraphicsPianoStripItem*> pianoStrips;

	void buildKey(int id, bool& isBlackKey, QColor &backgroundColor, QColor &bottomLineColor);\

	void pushKey();
	void popKey();

};

#endif // LPIANOPLAIN_H
