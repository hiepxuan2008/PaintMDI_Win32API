#include "stdafx.h"
#include "TextChildWindowData.h"

TextChildWindowData::TextChildWindowData()
{
}


TextChildWindowData::~TextChildWindowData()
{
}

void TextChildWindowData::onChooseColor(Color color)
{
	this->color = color;
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE); //Trick for redrawing edit control
}

void TextChildWindowData::onChooseFont(HFONT hFont)
{
	this->hFont = hFont;
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
}