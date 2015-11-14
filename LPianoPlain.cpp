#include "LPianoPlain.h"
#include <LGraphicsPianoStripItem.h>

#include <QDebug>
#include <QGraphicsLineItem>

const static int beatLength = 960;

LPianoPlain::LPianoPlain(QWidget *parent) :
	QGraphicsView(parent)
{
	keyOffset = 0;
	keyHeight = 14;
	internalLength = 1200;
	displayAmpitude = 1.0f;

	setStyleSheet("QGraphicsView { border-style: none; }");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(this);
	setScene(scene);

	//12 keys on default
	for(int i=0;i<12;i++)
		pushKey();

	for(int i=0;i*beatLength < internalLength;i++)
		pushBarLine();
}

void LPianoPlain::resizeEvent(QResizeEvent *event)
{
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
		pianoStrips[i]->setGeometry(QRect(0,(size-i-1)*keyHeight,internalLength*displayAmpitude,keyHeight));
	setSceneRect(scene->itemsBoundingRect());

	int barSize = beatBars.size();
	for(int i=0;i<barSize;i++)
	{
		float xCoord = i*beatLength*displayAmpitude;
		beatBars[i]->setLine(xCoord,0,xCoord,keyNum()*keyHeight-1);
	}


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

void LPianoPlain::setInternalLength(int length)
{
	if(internalLength > length)
	{
		while(beatBars.size()*beatLength > length)
			popBarLine();
	}
	else if(internalLength < length)
	{
		while(beatBars.size()*beatLength <= length)
			pushBarLine();
	}

	internalLength = length;
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
		pianoStrips[i]->setGeometry(QRect(0,(size-i-1)*keyHeight,internalLength,keyHeight));
}

void LPianoPlain::setKeyHeight(int height)
{
	keyHeight = height;
	resizeEvent(NULL);
}

void LPianoPlain::setAmplitude(float amp)
{
	displayAmpitude = amp;
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
	pianoStrip->setZValue(-1);

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

void LPianoPlain::pushBarLine()
{
	int size = beatBars.size();
	float xCoord = size*beatLength*displayAmpitude;
	QGraphicsLineItem* item = new QGraphicsLineItem(xCoord,0,xCoord,keyNum()*keyHeight-1);
	if(size%4 == 0)
		item->setPen(QPen(QColor::fromHsv(0,0,77),1,Qt::SolidLine));
	else
		item->setPen(QPen(QColor::fromHsv(51,48,189),1,Qt::SolidLine));
	scene->addItem(item);
	beatBars.push_back(item);
}

void LPianoPlain::popBarLine()
{
	QGraphicsLineItem* bar = beatBars[beatBars.size()-1];
	beatBars.pop_back();
	delete bar;
}
