#ifndef LPIANONOTE_H
#define LPIANONOTE_H

#include <QWidget>

class LPianoNote : public QWidget
{
	Q_OBJECT
public:
	explicit LPianoNote(QWidget *parent = 0);

	void paintEvent(QPaintEvent* event);

signals:

public slots:

};

#endif // LPIANONOTE_H
