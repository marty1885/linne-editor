#ifndef LPIANOKEY_H
#define LPIANOKEY_H

#include <QWidget>

namespace Linne
{
enum DisplayProperty
{
	Always,
	Never,
	Highlighted,
	NotHighlighted
};

inline bool shouldDisplay(bool isHighlighted,Linne::DisplayProperty property)
{
	if(property == Linne::Always)
		return true;
	else if(property == Linne::Never)
		return false;
	else if(isHighlighted == true)
	{
		return (property == Highlighted ? true : false);
	}

	return false;
}
}

//TODO: Implement a piano key widget

class LPianoKey : public QWidget
{
	Q_OBJECT
public:
	explicit LPianoKey(QWidget *parent = 0);


	void setText(QString str);
	void setBlackKey(bool blackKey);

	void setTextDisplayProperty(Linne::DisplayProperty prop);
	void setHighlightOnMouseEnter(bool autoHighLight);
	void setHighLight(bool highlight);
	void setBlackKeyLenghtRatio(float ratio);
	void setTextOffsetRatio(float ratio);

	bool highlight();

	QString text();
signals:
	void highlightClanged(bool highlight);

public slots:

protected:
	bool isBlackKey;
	QString keyText;
	bool isHighlighted;
	Linne::DisplayProperty textDisplayProperty;
	bool highlightOnMouseEnter;
	float blackKeyLenghtRatio;
	float textOffsetRatio;
	void paintEvent(QPaintEvent* event);

	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

};




#endif // LPIANOKEY_H
