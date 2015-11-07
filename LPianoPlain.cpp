#include "LPianoPlain.h"

#include <QGraphicsRectItem>
#include <LinneEditor.h>

LPianoPlain::LPianoPlain(QWidget *parent) :
	LGraphicsView(parent)
{
	keyHeight = 13;


	setStyleSheet("QGraphicsView { border-style: none; }");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(this);
	setScene(scene);

	for(int i=0;i<12;i++)
	{
		QGraphicsRectItem* pianoStrip = new QGraphicsRectItem();
		scene->addItem(pianoStrip);
		pianoStrip->setPen(Qt::NoPen);
		if(Linne::blackKeyList[i] == false)
			pianoStrip->setBrush(QColor::fromHsv(0,0,217));
		else
			pianoStrip->setBrush(QColor::fromHsv(0,0,191));
		pianoStrip->setZValue(-1);
		pianoStrip->setRect(0,height()-(i+1)*keyHeight,width(),keyHeight);
		pianoStrips.push_back(pianoStrip);
	}
}

void LPianoPlain::resizeEvent(QResizeEvent *event)
{
	int size = pianoStrips.size();
	for(int i=0;i<size;i++)
		pianoStrips[i]->setRect(QRect(0,height()-(i+1)*13,width(),13));
	translate(0,0);
}
