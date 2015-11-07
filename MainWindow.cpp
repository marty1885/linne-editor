#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <LPianoKey.h>

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
	pianoKey->setGeometry(10,10,100,15);
	pianoKey->setText("E3");
	pianoKey->setTextDisplayProperty(Linne::Highlighted);

}

MainWindow::~MainWindow()
{
	delete ui;
}
