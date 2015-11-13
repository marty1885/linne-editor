#ifndef LPIANOROLL_H
#define LPIANOROLL_H

#include <QWidget>
class LPianoKeyBoard;
class LPianoPlain;
class QScrollBar;
class QSlider;
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
	void onZoomSliderValueChanged(int val);
	void onPlainVerticalScrollbarValueChanged(int val);
	void onPlainHorizontalScrollbarValueChanged(int val);

protected:
	LPianoKeyBoard* keyboard;
	LPianoPlain* plain;
	QScrollBar* verticalScrollBar;
	QScrollBar* horizontalScrollBar;
	QSlider* zoomSloder;

	void adjustScrollBars();

};

#endif // LPIANOROLL_H
