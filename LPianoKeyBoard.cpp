#include "LPianoKeyBoard.h"
#include <LPianoKey.h>
#include <QGraphicsProxyWidget>

#include <QDebug>

LPianoKeyBoard::LPianoKeyBoard(QWidget *parent) :
	QGraphicsView(parent)
{
	keyOffset = 0;

	setStyleSheet("QGraphicsView { border-style: none; }");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(this);
	setScene(scene);


	for(int i=0;i<12;i++)
		pushKey();
}

void LPianoKeyBoard::resizeEvent(QResizeEvent *event)
{
	int size = keys.size();
	for(int i=0;i<size;i++)
		keys[i]->setGeometry(QRect(0,height()-(i+1)*15,width(),15));
	setSceneRect(0,0,width(),height());
}

void LPianoKeyBoard::setKeyOffset(int offset)
{
	keyOffset = offset;
	int size = keys.size();
	for(int i=0;i<size;i++)
	{
		LPianoKey* key = keys[i];
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

void LPianoKeyBoard::onKeyClicked()
{
	QObject* senderPtr = QObject::sender();
	LPianoKey* clickedKey = (LPianoKey*)senderPtr;
	int index = keys.indexOf(clickedKey);
	qDebug() << index;
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

void LPianoKeyBoard::pushKey()
{
	int index = keys.size();
	LPianoKey* key = new LPianoKey;
	int id = index + keyOffset;

	QString keyName;
	bool isBlackKey;
	Linne::DisplayProperty prop;
	buildKey(id, keyName, isBlackKey, prop);

	scene->addWidget(key);
	key->setGeometry(QRect(0,height()-(index+1)*15,width(),15));
	key->setText(keyName);
	key->setBlackKey(isBlackKey);
	key->setTextDisplayProperty(prop);
	QObject::connect(key,SIGNAL(clicked()),SLOT(onKeyClicked()));

	keys.push_back(key);
}

void LPianoKeyBoard::popKey()
{
	LPianoKey* key = keys[keys.size()-1];
	keys.pop_back();
	delete key;
	resizeEvent(NULL);
}
