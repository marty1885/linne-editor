#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LPianoKey;
class LPianoKeyBoard;
class LPianoNote;
class LPianoPlain;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

protected:
	LPianoKey* pianoKey;
	LPianoKeyBoard* keyBoard;
	LPianoNote* note;
	LPianoPlain* pianoPlain;

};

#endif // MAINWINDOW_H
