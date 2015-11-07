#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <LPianoKey.h>
#include <LPianoKeyBoard.h>
#include <LPianoNote.h>

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
}

MainWindow::~MainWindow()
{
	delete ui;
}
