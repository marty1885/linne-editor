#include "LPianoKeyBoard.h"
#include <LPianoKey.h>
#include <QGraphicsProxyWidget>

#include <QDebug>

LPianoKeyBoard::LPianoKeyBoard(QWidget *parent) :
	LGraphicsView(parent)
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

void LPianoKeyBoard::resizeEvent(QResizeEvent *event)
{
	int size = pianoKeys.size();
	for(int i=0;i<size;i++)
		pianoKeys[i]->setGeometry(QRect(0,(size-i-1)*keyHeight,width(),keyHeight));
	translate(0,0);
}

void LPianoKeyBoard::setKeyNum(int num)
{
	int keyNum = pianoKeys.size();
	if(keyNum > num)
	{
		for(int i=0;i<keyNum-num;i++)
			popKey();
	}
	else
		for(int i=0;i<num-keyNum;i++)
			pushKey();
}

void LPianoKeyBoard::setKeyOffset(int offset)
{
	keyOffset = offset;
	int size = pianoKeys.size();
	for(int i=0;i<size;i++)
	{
		LPianoKey* key = pianoKeys[i];
		int id = i + keyOffset;
		QString keyName;
		bool isBlackKey;
		Linne::DisplayProperty prop;
		buildKey(id, keyName, isBlackKey, prop);
		key->setText(keyName);
		key->setBlackKey(isBlackKey);
		key->setTextDisplayProperty(prop);
	}
}

void LPianoKeyBoard::setKeyHeight(int height)
{
	keyHeight = height;
	resizeEvent(NULL);
}

LPianoKey** LPianoKeyBoard::keys()
{
	return &(pianoKeys[0]);
}

int LPianoKeyBoard::keyNum()
{
	return pianoKeys.size();
}

int LPianoKeyBoard::getKeyHeight()
{
	return keyHeight;
}

void LPianoKeyBoard::onKeyClicked()
{
	QObject* senderPtr = QObject::sender();
	LPianoKey* clickedKey = (LPianoKey*)senderPtr;
	int index = pianoKeys.indexOf(clickedKey);
	emit keyClicked(index+keyOffset);
}

void LPianoKeyBoard::buildKey(int id, QString &name, bool &blackKey, Linne::DisplayProperty &prop)
{
	int level = id/12 + (id < 0 ? -1 : 0);
	int dataIndex = id%12 + (id >= 0 ? 0 : 12);
	name = Linne::keyNames[dataIndex]+tr("%1").arg(level);
	blackKey = Linne::blackKeyList[dataIndex];

	if(dataIndex%12 != 0)
		prop = Linne::Highlighted;
	else
		prop = Linne::Always;
}

//TODO : check is setGeometry here is correct
void LPianoKeyBoard::pushKey()
{
	int index = pianoKeys.size();
	LPianoKey* key = new LPianoKey;
	int id = index + keyOffset;

	QString keyName;
	bool isBlackKey;
	Linne::DisplayProperty prop;
	buildKey(id, keyName, isBlackKey, prop);

	scene->addWidget(key);
	key->setGeometry(QRect(0,(index+1)*keyHeight,width(),keyHeight));
	key->setText(keyName);
	key->setBlackKey(isBlackKey);
	key->setTextDisplayProperty(prop);
	QObject::connect(key,SIGNAL(clicked()),SLOT(onKeyClicked()));

	pianoKeys.push_back(key);
}

void LPianoKeyBoard::popKey()
{
	LPianoKey* key = pianoKeys[pianoKeys.size()-1];
	pianoKeys.pop_back();
	delete key;
	resizeEvent(NULL);
}
