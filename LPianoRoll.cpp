#include "LPianoRoll.h"

#include <LPianoKeyBoard.h>
#include <LPianoPlain.h>
#include <QScrollBar>
#include <LPianoKey.h>

#include <QDebug>
#include <QWheelEvent>
#include <QGuiApplication>

LPianoRoll::LPianoRoll(QWidget *parent) :
	QWidget(parent)
{
	ctrlPressed = false;

	keyboard = new LPianoKeyBoard(this);
	keyboard->setKeyNum(72);

	plain = new LPianoPlain(this);
	plain->setKeyNum(72);
	plain->addNote(0,0,83);
	//plain->scale(1,2);

	verticalScrollBar = new QScrollBar(this);
	verticalScrollBar->setGeometry(width()-12,0,12,height());
	verticalScrollBar->setMinimum(0);

	horizontalScrollBar = new QScrollBar(Qt::Horizontal,this);
	horizontalScrollBar->setGeometry(0,height()-12,width()-12,12);

	QObject::connect(verticalScrollBar,SIGNAL(valueChanged(int)),SLOT(onVerticalScrollbarValueChanged(int)));
	QObject::connect(horizontalScrollBar,SIGNAL(valueChanged(int)),SLOT(onHorizontalScrollbarValueChanged(int)));
	QObject::connect(plain,SIGNAL(mouseHoverChanged(int)),SLOT(onPianoPlainHoverChanged(int)));
}

void LPianoRoll::resizeEvent(QResizeEvent *event)
{
	keyboard->setGeometry(0,0,83,height()-12);
	plain->setGeometry(84,0,width()-84-12,height()-12);
	verticalScrollBar->setGeometry(width()-12,0,12,height()-12);
	horizontalScrollBar->setGeometry(83,height()-12,width()-12-83,12);

	verticalScrollBar->setMaximum(keyboard->keyNum()*keyboard->getKeyHeight()-height()+12);
	const int oveLength = 3000;
	horizontalScrollBar->setMaximum(oveLength-plain->geometry().width());
	plain->setInternalLength(oveLength);
}

void LPianoRoll::wheelEvent(QWheelEvent *event)
{
	if(QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier))
	{
		int currentVal = verticalScrollBar->value();
		int step = verticalScrollBar->singleStep();
		verticalScrollBar->setValue(currentVal+(-event->delta()/120.0f)*4.3*step);
	}
	else
	{
		int currentVal = horizontalScrollBar->value();
		int step = horizontalScrollBar->singleStep();
		horizontalScrollBar->setValue(currentVal+(-event->delta()/120.0f)*step);
	}
	QWidget::wheelEvent(event);
}

void LPianoRoll::onVerticalScrollbarValueChanged(int val)
{
	//qDebug() << val;
	static int lastVal = 0.0f;
	keyboard->translate(0,val-lastVal);
	plain->translate(0,val-lastVal);
	lastVal = val;
}

void LPianoRoll::onHorizontalScrollbarValueChanged(int val)
{
	static int lastVal = 0.0f;
	plain->translate(val-lastVal,0);
	lastVal = val;
}

void LPianoRoll::onPianoPlainHoverChanged(int id)
{
	static int lastKey = 0;
	if(id > 0)
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
