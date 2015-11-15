#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <QGraphicsView>
#include <QVector>

#include <LinneEditor.h>

class LPianoKey;
class LGraphicsPianoStripItem;
class LPianoNote;
class QGraphicsLineItem;
class QGraphicsProxyWidget;

class LNote
{
public:
	QString lyric;
	int pitch;
	int location;
	int length;
};

class LPianoPlain : public QGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void leaveEvent(QEvent* event);
	void mousePressEvent(QMouseEvent *event);

	void setKeyNum(int num);
	void setKeyOffset(int offset);
	void setInternalLength(int length);
	void setKeyHeight(int height);
	void setAmplitude(float amp);
	void setQuantization(int quanti);

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
	QVector<LNote> notes;
	QVector<LPianoNote*> pianoNotes;
	QGraphicsScene* scene;

	int keyOffset;
	int keyHeight;
	int internalLength;
	float displayAmpitude;
	int currentHover;
	int quantization;

	void buildKey(int id, bool &isBlackKey, QColor& backgroundColor, QColor& bottomLineColor);
	void pushKey();
	void popKey();

	void pushBarLine();
	void popBarLine();
};

#endif // LPIANOPLAIN_H
