#include "LPianoPlain.h"

#include <LinneEditor.h>
#include <LGraphicsPianoStripItem.h>
#include <LPianoNote.h>

#include <QMouseEvent>
#include <QDebug>

LPianoPlain::LPianoPlain(QWidget *parent) :
	LGraphicsView(parent)
{
	keyHeight = 14;
	keyOffset = 0;
	internalLength = 1200;
	lastHoverId = -1;

	setMouseTracking(true);
	setStyleSheet("QGraphicsView { border-style: none; }");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(this);
	setScene(scene);

	for(int i=0;i<12;i++)
		pushKey();
}

void LPianoPlain::resizeEvent(QResizeEvent *event)
{
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
		pianoStrips[i]->setGeometry(0,(size-i-1)*keyHeight,internalLength,keyHeight);
	translate(0,0);
}

void LPianoPlain::setKeyNum(int num)
{
	int keyNum = pianoStrips.size();
	if(keyNum > num)
	{
		for(int i=0;i<keyNum-num;i++)
			popKey();
	}
	else
		for(int i=0;i<num-keyNum;i++)
			pushKey();
}

void LPianoPlain::setKeyOffset(int offset)
{
	keyOffset = offset;
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
	{
		LGraphicsPianoStripItem* pianoStrip = pianoStrips[i];
		int id = i + keyOffset;
		bool isBlackKey;
		QColor backgroundColor;
		QColor bottomLineColor;
		buildKey(id, isBlackKey,backgroundColor,bottomLineColor);
		pianoStrip->setBlackKey(isBlackKey);
		pianoStrip->setBackgroundColor(backgroundColor);
		pianoStrip->setbottomLineColor(bottomLineColor);
	}
	resizeEvent(NULL);
}

void LPianoPlain::mouseMoveEvent(QMouseEvent *event)
{
	int size = pianoStrips.size();
	int id = 0;
	bool found = false;
	qDebug() << translateVec;
	for(int i=0;i<size;i++)
	{
		LGraphicsPianoStripItem* item = pianoStrips[i];
		QRectF rect = item->sceneBoundingRect();
		QVector2D posVec(event->x()+translateVec.x(),event->y()+translateVec.y());
		QPoint point = mapFromGlobal(QPoint(posVec.x(),posVec.y()));
		QRectF pos(point.x(),point.y(),point.x(),point.y());
		qDebug() << point;
		if(rect.intersects(pos))//TODO: This ignores any transformation
		{
			found = true;
			id = i+keyOffset;
			break;
		}

	}
	//int id = size - (event->y()+sceneRect().y())/keyHeight + keyOffset-1;
	LGraphicsView::mouseMoveEvent(event);
	if(id != lastHoverId && found == true)
	{
		emit mouseHoverChanged(id);
		lastHoverId = id;
	}
}

void LPianoPlain::leaveEvent(QEvent *event)
{
	lastHoverId = -1;
	emit mouseHoverChanged(-1);
	LGraphicsView::leaveEvent(event);
}

void LPianoPlain::setInternalLength(int length)
{
	internalLength = length;
	resizeEvent(NULL);
}

LPianoNote* LPianoPlain::addNote(int id, int location, int length)
{
	int size = pianoStrips.size();
	int index = id-keyOffset;
	int yCoord = (size-index-1)*keyHeight;
	LPianoNote* note = new LPianoNote;
	scene->addWidget(note);
	note->setGeometry(location,yCoord,length,keyHeight);
	notes.push_back(note);
	return note;
}

void LPianoPlain::buildKey(int id, bool &isBlackKey, QColor& backgroundColor, QColor& bottomLineColor)
{
	int dataIndex = id%12 + (id >= 0 ? 0 : 12);
	isBlackKey = Linne::blackKeyList[dataIndex];
	if(isBlackKey == true)
		backgroundColor = QColor::fromHsv(0,0,191);
	else
		backgroundColor = QColor::fromHsv(0,0,217);

	if(id%12 == 0)
		bottomLineColor = QColor::fromHsv(51,48,189);
	else if(isBlackKey == true)
		bottomLineColor = QColor::fromHsv(0,0,170);
	else
		bottomLineColor = QColor::fromHsv(0,0,196);
}

//TODO : check is setGeometry here is correct
void LPianoPlain::pushKey()
{
	int size = pianoStrips.size();;\
	int id = size+keyOffset;
	bool isBlackKey;
	QColor backgroundColor;
	QColor bottomLineColor;
	buildKey(id, isBlackKey,backgroundColor,bottomLineColor);
	LGraphicsPianoStripItem* pianoStrip = new LGraphicsPianoStripItem();
	scene->addItem(pianoStrip);
	pianoStrip->setBlackKey(isBlackKey);
	pianoStrip->setBackgroundColor(backgroundColor);
	pianoStrip->setbottomLineColor(bottomLineColor);

	pianoStrip->setZValue(-2);
	pianoStrip->setGeometry(0,height()-(size+1)*keyHeight,internalLength,keyHeight);
	pianoStrips.push_back(pianoStrip);
}

void LPianoPlain::popKey()
{
	LGraphicsPianoStripItem* pianoStrip = pianoStrips[pianoStrips.size()-1];
	pianoStrips.pop_back();
	delete pianoStrip;
}
