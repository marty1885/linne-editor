#ifndef LPIANOKEYBOARD_H
#define LPIANOKEYBOARD_H

#include <QGraphicsView>
#include <QVector>
#include <QPair>

#include <LinneEditor.h>
#include <LGraphicsView.h>

//TODO: add a new widget that workes arround QGraphicsView's shitty bugs.

class LPianoKey;

class LPianoKeyBoard : public LGraphicsView
{
	Q_OBJECT
public:
	explicit LPianoKeyBoard(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *event);
	void setKeyNum(int num);

	void setKeyOffset(int offset);

signals:
	void keyClicked(int id);

public slots:
	void onKeyClicked();

protected:
	QVector<LPianoKey*> keys;
	QGraphicsScene* scene;

	int keyOffset;

	void buildKey(int id, QString& name, bool& blackKey, Linne::DisplayProperty& prop);
	void pushKey();
	void popKey();
};

#endif // LPIANOKEYBOARD_H
