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
class LPianoRoll;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	void resizeEvent(QResizeEvent* event);
	~MainWindow();

public slots:

private:
	Ui::MainWindow *ui;

protected:
	LPianoRoll* pianoRoll;

};

#endif // MAINWINDOW_H
