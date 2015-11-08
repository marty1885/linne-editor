#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <LPianoKey.h>
#include <LPianoKeyBoard.h>
#include <LPianoNote.h>
#include <LPianoPlain.h>
#include <LPianoRoll.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("Linne Editor");

	//Setp Icon
	QPixmap pmap;
	pmap.load("data/icon.png");
	pmap = pmap.scaled(1024,1024,Qt::KeepAspectRatio);//Limit to 1024*1024 as X11's max icon size
	QIcon windowIcon(pmap);
	setWindowIcon(windowIcon);


	//Widget testing
	pianoKey = new LPianoKey(this);
	pianoKey->setGeometry(10,10,83,15);
	pianoKey->setText("E3");
	pianoKey->setTextDisplayProperty(Linne::Highlighted);

	keyBoard = new LPianoKeyBoard(this);
	keyBoard->setGeometry(200,10,83,280);
	keyBoard->setKeyNum(20);

	note = new LPianoNote(this);
	note->setGeometry(10,30,83,13);
	note->setText("a");

	pianoPlain = new LPianoPlain(this);
	pianoPlain->setGeometry(283,10,260,280);
	pianoPlain->setKeyNum(20);

	pianoRoll = new LPianoRoll(this);
	pianoRoll->setGeometry(200,330,800,280);

	QObject::connect(pianoPlain,SIGNAL(mouseHoverChanged(int)),SLOT(onPianoPlainHoverChanged(int)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onPianoPlainHoverChanged(int id)
{
	static int lastKey = 0;
	if(id >= 0)
	{
		keyBoard->keys()[lastKey]->setHighLight(false);
		keyBoard->keys()[id]->setHighLight(true);
		lastKey = id;
	}
	else
	{
		keyBoard->keys()[lastKey]->setHighLight(false);
		lastKey = 0;
	}
}
