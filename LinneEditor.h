#ifndef LINNEEDITOR_H
#define LINNEEDITOR_H

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

static const bool blackKeyList[] = {false, true, false, true, false, false, true, false, true, false, true, false};
static const char keyNames[12][3] = {"C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};

}

#endif // LINNEEDITOR_H
