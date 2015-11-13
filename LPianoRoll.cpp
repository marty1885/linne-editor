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
	ctrlPressed = false;

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

	adjustScrollBars();
}


void LPianoRoll::resizeEvent(QResizeEvent *event)
{
	//Adjust widgets
	keyboard->setGeometry(0,0,83,height()-12);
	plain->setGeometry(84,0,width()-84-12,height()-12);
	verticalScrollBar->setGeometry(width()-12,0,12,height()-12);
	horizontalScrollBar->setGeometry(83,height()-12,width()-12-83-93,12);
	zoomSloder->setGeometry(width()-96,height()-12,96-12,12);

	//Adjust scrollbar attributes
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
	//QWidget::wheelEvent(event);
}

void LPianoRoll::onVerticalScrollbarValueChanged(int val)
{
	//qDebug() << val;
//	keyboard->translate(horizontalScrollBar->value(),val);
//	plain->translate(horizontalScrollBar->value(),val);
}

void LPianoRoll::onHorizontalScrollbarValueChanged(int val)
{
//	plain->translate(val,verticalScrollBar->value());
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

void LPianoRoll::adjustScrollBars()
{
	verticalScrollBar->setMaximum(keyboard->verticalScrollBar()->maximum());
	verticalScrollBar->setMinimum(keyboard->verticalScrollBar()->minimum());
	verticalScrollBar->setValue(keyboard->verticalScrollBar()->value());
	verticalScrollBar->setPageStep(keyboard->verticalScrollBar()->pageStep());

	horizontalScrollBar->setMaximum(plain->horizontalScrollBar()->maximum());
	horizontalScrollBar->setMinimum(plain->horizontalScrollBar()->minimum());
	horizontalScrollBar->setValue(plain->horizontalScrollBar()->value());
	horizontalScrollBar->setPageStep(plain->horizontalScrollBar()->pageStep());
}
