#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <QGraphicsView>
#include <QVector>

#include <LinneEditor.h>

class LPianoKey;
class LGraphicsPianoStripItem;
class QGraphicsLineItem;

class LPianoPlain : public QGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void leaveEvent(QEvent* event);

	void setKeyNum(int num);
	void setKeyOffset(int offset);
	void setInternalLength(int length);
	void setKeyHeight(int height);
	void setAmplitude(float amp);

	int keyNum();
	int getKeyHeight();
	int getKeyOffset();

signals:
	void mouseHoverChanged(int index);

public slots:
	void onPianoStripMouseHover();

protected:
	QVector<LGraphicsPianoStripItem*> pianoStrips;
	QVector<QGraphicsLineItem*> beatBars;
	QGraphicsScene* scene;

	int keyOffset;
	int keyHeight;
	int internalLength;
	float displayAmpitude;

	void buildKey(int id, bool &isBlackKey, QColor& backgroundColor, QColor& bottomLineColor);
	void pushKey();
	void popKey();

	void pushBarLine();
	void popBarLine();
};

#endif // LPIANOPLAIN_H
