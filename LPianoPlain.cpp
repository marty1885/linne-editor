#include "LPianoPlain.h"
#include <LGraphicsPianoStripItem.h>

#include <QDebug>

LPianoPlain::LPianoPlain(QWidget *parent) :
	QGraphicsView(parent)
{
	keyOffset = 0;
	keyHeight = 14;

	setStyleSheet("QGraphicsView { border-style: none; }");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(this);
	setScene(scene);

	//12 keys on default
	for(int i=0;i<12;i++)
		pushKey();
}

void LPianoPlain::resizeEvent(QResizeEvent *event)
{
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
		pianoStrips[i]->setGeometry(QRect(0,(size-i-1)*keyHeight,width(),keyHeight));
	setSceneRect(scene->itemsBoundingRect());

	QGraphicsView::resizeEvent(event);
	//qDebug() << verticalScrollBar()->maximum();
}

void LPianoPlain::leaveEvent(QEvent *event)
{
	emit mouseHoverChanged(-1);
	QGraphicsView::leaveEvent(event);
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
}

void LPianoPlain::setKeyHeight(int height)
{
	keyHeight = height;
	resizeEvent(NULL);
}

int LPianoPlain::keyNum()
{
	return pianoStrips.size();
}

int LPianoPlain::getKeyHeight()
{
	return keyHeight;
}

int LPianoPlain::getKeyOffset()
{
	return keyOffset;
}

void LPianoPlain::onPianoStripMouseHover()
{
	QObject* senderPtr = QObject::sender();
	LGraphicsPianoStripItem* sender = (LGraphicsPianoStripItem*)senderPtr;
	int index = pianoStrips.indexOf(sender);
	emit mouseHoverChanged(index);
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
	int index = pianoStrips.size();
	LGraphicsPianoStripItem* pianoStrip = new LGraphicsPianoStripItem;
	int id = index + keyOffset;

	bool isBlackKey;
	QColor backgroundColor;
	QColor bottomLineColor;
	buildKey(id, isBlackKey,backgroundColor,bottomLineColor);
	pianoStrip->setBlackKey(isBlackKey);
	pianoStrip->setBackgroundColor(backgroundColor);
	pianoStrip->setbottomLineColor(bottomLineColor);

	scene->addItem(pianoStrip);
	pianoStrip->setGeometry(QRect(0,(index+1)*keyHeight,width(),keyHeight));
	QObject::connect(pianoStrip,SIGNAL(mouseEntered()),SLOT(onPianoStripMouseHover()));

	pianoStrips.push_back(pianoStrip);
}

void LPianoPlain::popKey()
{
	LGraphicsPianoStripItem* pianoStrip = pianoStrips[pianoStrips.size()-1];
	pianoStrips.pop_back();
	delete pianoStrip;
	resizeEvent(NULL);
}
