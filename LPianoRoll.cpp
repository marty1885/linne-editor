#include "LPianoRoll.h"

#include <math.h>

#include <LPianoKeyBoard.h>
#include <LPianoPlain.h>
#include <QScrollBar>
#include <LPianoKey.h>

#include <QDebug>
#include <QWheelEvent>
#include <QGuiApplication>
#include <QSlider>

LPianoRoll::LPianoRoll(QWidget *parent) :
	QWidget(parent)
{

	keyboard = new LPianoKeyBoard(this);
	keyboard->setKeyNum(72);

	plain = new LPianoPlain(this);
	plain->setKeyNum(72);

	verticalScrollBar = new QScrollBar(this);
	verticalScrollBar->setGeometry(width()-12,0,12,height());
	verticalScrollBar->setMinimum(0);

	horizontalScrollBar = new QScrollBar(Qt::Horizontal,this);
	horizontalScrollBar->setGeometry(0,height()-12,width()-12,12);

	zoomSloder = new QSlider(Qt::Horizontal,this);
	zoomSloder->setGeometry(width()-83,height()-12,width()-83,12);
	zoomSloder->setMinimum(1);
	zoomSloder->setValue(zoomSloder->maximum());

	QObject::connect(verticalScrollBar,SIGNAL(valueChanged(int)),SLOT(onVerticalScrollbarValueChanged(int)));
	QObject::connect(horizontalScrollBar,SIGNAL(valueChanged(int)),SLOT(onHorizontalScrollbarValueChanged(int)));
	QObject::connect(plain,SIGNAL(mouseHoverChanged(int)),SLOT(onPianoPlainHoverChanged(int)));
	QObject::connect(zoomSloder,SIGNAL(valueChanged(int)),SLOT(onZoomSliderValueChanged(int)));
	QObject::connect(plain->verticalScrollBar(),SIGNAL(valueChanged(int)),SLOT(onPlainVerticalScrollbarValueChanged(int)));
	QObject::connect(plain->horizontalScrollBar(),SIGNAL(valueChanged(int)),SLOT(onPlainHorizontalScrollbarValueChanged(int)));
	QObject::connect(keyboard->verticalScrollBar(),SIGNAL(valueChanged(int)),SLOT(onPlainVerticalScrollbarValueChanged(int)));
}


void LPianoRoll::resizeEvent(QResizeEvent *event)
{
	//Adjust widgets
	keyboard->setGeometry(0,0,83,height()-12);
	plain->setGeometry(84,0,width()-84-12,height()-12);
	verticalScrollBar->setGeometry(width()-12,0,12,height()-12);
	horizontalScrollBar->setGeometry(83,height()-12,width()-12-83-93,12);
	zoomSloder->setGeometry(width()-96,height()-12,96-12,12);

	//TODO: Add initlization code
	static bool firstRun = true;
	if(firstRun == true)
	{
		plain->resizeEvent(NULL);
		keyboard->resizeEvent(NULL);
		firstRun = false;
	}
	adjustScrollBars();
}

void LPianoRoll::wheelEvent(QWheelEvent *event)
{
//	if(QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier))
//	{
//		int currentVal = verticalScrollBar->value();
//		int step = verticalScrollBar->singleStep();
//		verticalScrollBar->setValue(currentVal+(-event->delta()/120.0f)*4.3*step);
//	}
//	else
//	{
//		int currentVal = horizontalScrollBar->value();
//		int step = horizontalScrollBar->singleStep();
//		horizontalScrollBar->setValue(currentVal+(-event->delta()/120.0f)*step);
//	}
}

void LPianoRoll::onVerticalScrollbarValueChanged(int val)
{
	plain->verticalScrollBar()->setValue(val);
	keyboard->verticalScrollBar()->setValue(val);
}

void LPianoRoll::onHorizontalScrollbarValueChanged(int val)
{
	plain->verticalScrollBar()->setValue(val);
}

void LPianoRoll::onPianoPlainHoverChanged(int id)
{
	static int lastKey = 0;
	if(id >= 0)
	{
		keyboard->keys()[lastKey]->setHighLight(false);
		keyboard->keys()[id]->setHighLight(true);
		lastKey = id;
	}
	else
	{
		keyboard->keys()[lastKey]->setHighLight(false);
		lastKey = 0;
	}
}

void LPianoRoll::onZoomSliderValueChanged(int val)
{
	static float lastScale = 1.0f;
	float scaling = sqrt((float)val/zoomSloder->maximum());
	plain->scale(1/lastScale,1);
	plain->scale(scaling,1);
	lastScale = scaling;

}

void LPianoRoll::onPlainVerticalScrollbarValueChanged(int val)
{
	verticalScrollBar->setValue(val);
	plain->verticalScrollBar()->setValue(val);
	keyboard->verticalScrollBar()->setValue(val);
}

void LPianoRoll::onPlainHorizontalScrollbarValueChanged(int val)
{
	horizontalScrollBar->setValue(val);
}

void LPianoRoll::adjustScrollBars()
{
	verticalScrollBar->setMaximum(plain->verticalScrollBar()->maximum());
	verticalScrollBar->setMinimum(plain->verticalScrollBar()->minimum());
	verticalScrollBar->setValue(plain->verticalScrollBar()->value());
	verticalScrollBar->setPageStep(plain->verticalScrollBar()->pageStep());

	horizontalScrollBar->setMaximum(plain->horizontalScrollBar()->maximum());
	horizontalScrollBar->setMinimum(plain->horizontalScrollBar()->minimum());
	horizontalScrollBar->setValue(plain->horizontalScrollBar()->value());
	horizontalScrollBar->setPageStep(plain->horizontalScrollBar()->pageStep());

	//Disable it if useless
	if(verticalScrollBar->maximum() == verticalScrollBar->minimum())
		verticalScrollBar->setEnabled(false);
	else
		verticalScrollBar->setEnabled(true);

	if(horizontalScrollBar->maximum() == horizontalScrollBar->minimum())
		horizontalScrollBar->setEnabled(false);
	else
		horizontalScrollBar->setEnabled(true);
}

