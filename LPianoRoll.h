#ifndef LPIANOROLL_H
#define LPIANOROLL_H

#include <QWidget>
class LPianoKeyBoard;
class LPianoPlain;
class QScrollBar;
class LPianoRoll : public QWidget
{
	Q_OBJECT
public:
	explicit LPianoRoll(QWidget *parent = 0);
	void resizeEvent(QResizeEvent* event);
	void wheelEvent(QWheelEvent* event);

signals:

public slots:
	void onVerticalScrollbarValueChanged(int val);
	void onHorizontalScrollbarValueChanged(int val);
	void onPianoPlainHoverChanged(int id);

protected:
	LPianoKeyBoard* keyboard;
	LPianoPlain* plain;
	QScrollBar* verticalScrollBar;
	QScrollBar* horizontalScrollBar;

	bool ctrlPressed;

};

#endif // LPIANOROLL_H
