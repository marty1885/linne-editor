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

	pianoRoll = new LPianoRoll(this);
	pianoRoll->setGeometry(10,10,width()-10,height()-10);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	pianoRoll->setGeometry(10,10,width()-10,height()-10);
}

MainWindow::~MainWindow()
{
	delete ui;
}
