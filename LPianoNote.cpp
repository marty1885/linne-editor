#include "LPianoNote.h"
#include <QPainter>

LPianoNote::LPianoNote(QWidget *parent) :
	QWidget(parent)
{
}

void LPianoNote::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.fillRect(0,0,width()-1,height()-1,QColor::fromHsv(77,156,219));

	painter.setPen(QColor::fromHsv(330,5,125));
	QLineF lines[] = {QLineF(0,0,0,height()-1),QLineF(0,height()-1,width()-1,height()-1),
			QLineF(width()-1,height()-1,width()-1,0),QLineF(width()-1,0,0,0)};
	painter.drawLines(lines,4);
}
