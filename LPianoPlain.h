#ifndef LPIANOPLAIN_H
#define LPIANOPLAIN_H

#include <LGraphicsView.h>
#include <QVector>

class LGraphicsPianoStripItem;
class LPianoNote;

class LPianoPlain : public LGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoPlain(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void setKeyNum(int num);
	void setKeyOffset(int offset);
	void mouseMoveEvent(QMouseEvent* event);
	void leaveEvent(QEvent* event);
	void setInternalLength(int length);

	LPianoNote* addNote(int id, int location, int length);

signals:
	void mouseHoverChanged(int id);

public slots:

protected:
	int keyHeight;
	int keyOffset;
	int internalLength;
	int lastHoverId;

	QGraphicsScene* scene;
	QVector<LGraphicsPianoStripItem*> pianoStrips;
	QVector<LPianoNote*> notes;

	void buildKey(int id, bool& isBlackKey, QColor &backgroundColor, QColor &bottomLineColor);

	void pushKey();
	void popKey();

};

#endif // LPIANOPLAIN_H
