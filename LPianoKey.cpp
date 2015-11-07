#include "LPianoKey.h"
#include <QPainter>

#include <QDebug>

LPianoKey::LPianoKey(QWidget *parent) :
	QAbstractButton(parent)
{
	isBlackKey = false;
	isHighlighted = false;
	textDisplayProperty = Linne::Always;
	highlightOnMouseEnter = true;
	blackKeyLenghtRatio = 11.0f/20;
	textOffsetRatio = 1.0f/9;
}

void LPianoKey::setText(QString str)
{
	keyText = str;
	repaint();
}

void LPianoKey::setBlackKey(bool blackKey)
{
	isBlackKey = blackKey;
	repaint();
}

QString LPianoKey::text()
{
	return keyText;
}

void LPianoKey::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(0,0,width()-1,height()-1,QColor::fromHsv(0,0,242));

	painter.setPen(QColor::fromHsv(0,0,219));
	painter.drawLine(0,height()-1,width()-1, height()-1);
	painter.drawLine(width()-1, 0,width()-1, height());

	if(isBlackKey == true)
	{
		painter.fillRect(0,0,width()*blackKeyLenghtRatio, height()-1,QColor::fromHsv(0,0,48));

		painter.setPen(QColor::fromHsv(0,0,29));
		painter.drawLine(width()*blackKeyLenghtRatio,0,width()*blackKeyLenghtRatio,height()-1);
		painter.drawLine(0,height()-1,width()*blackKeyLenghtRatio,height()-1);
	}

	if(isHighlighted == true)
		painter.fillRect(width()*blackKeyLenghtRatio+1,0,width()*(1-blackKeyLenghtRatio),height()-1,QColor::fromHsv(183,242,245));

	if(shouldDisplay(isHighlighted, textDisplayProperty) == true)
	{
		QFont font = painter.font();
		font.setPixelSize(height()*(9.0f/13));
		painter.setFont(font);
		painter.setPen(QColor::fromHsv(0,0,98));

		painter.drawText(width()*(blackKeyLenghtRatio+textOffsetRatio),2,width()*(1-blackKeyLenghtRatio+textOffsetRatio),height(),Qt::AlignBaseline,keyText);
	}

}

void LPianoKey::enterEvent(QEvent *event)
{
	setHighLight(true);
	repaint();
}

void LPianoKey::leaveEvent(QEvent *event)
{
	setHighLight(false);
	repaint();
}


void LPianoKey::setTextDisplayProperty(Linne::DisplayProperty prop)
{
	textDisplayProperty = prop;
	repaint();
}

void LPianoKey::setHighlightOnMouseEnter(bool autoHighLight)
{
	highlightOnMouseEnter = autoHighLight;
	repaint();
}

void LPianoKey::setHighLight(bool highlight)
{
	bool changed = false;
	if(isHighlighted != highlight)
		changed = true;
	isHighlighted = highlight;
	repaint();

	if(changed == true)
		emit highlightClanged(highlight);
}

void LPianoKey::setBlackKeyLenghtRatio(float ratio)
{
	blackKeyLenghtRatio = ratio;
}

void LPianoKey::setTextOffsetRatio(float ratio)
{
	textOffsetRatio = ratio;
}

bool LPianoKey::highlight()
{
	return isHighlighted;
}
