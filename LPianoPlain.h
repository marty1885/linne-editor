#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <QGraphicsView>
#include <QVector>

#include <LinneEditor.h>

class LPianoKey;
class LGraphicsPianoStripItem;

class LPianoPlain : public QGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void setKeyNum(int num);
	void setKeyOffset(int offset);
	void setKeyHeight(int height);

	int keyNum();
	int getKeyHeight();

signals:

public slots:

protected:
	QVector<LGraphicsPianoStripItem*> pianoStrips;
	QGraphicsScene* scene;

	int keyOffset;
	int keyHeight;

	void buildKey(int id, bool &isBlackKey, QColor& backgroundColor, QColor& bottomLineColor);
	void pushKey();
	void popKey();
};

#endif // LPIANOPLAIN_H
