#ifndef LPIANONOTE_H
#define LPIANONOTE_H

#include <QWidget>
#include <QString>

class LPianoNote : public QWidget
{
	Q_OBJECT
public:
	explicit LPianoNote(QWidget *parent = 0);

	void paintEvent(QPaintEvent* event);
	void setText(QString str);

signals:

public slots:

protected:
	QString displayText;

};

#endif // LPIANONOTE_H
