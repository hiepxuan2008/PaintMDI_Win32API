#pragma once
#include "stdafx.h"
#include "Attributes/Color.h"
#include "ChildWindowData.h"

class TextChildWindowData : public ChildWindowData
{
public:
	HWND hOwnerWnd;
	HWND hEdit;
	HFONT hFont;
	Color color;

public:
	TextChildWindowData();
	~TextChildWindowData();

public:
	void onChooseColor(Color color); //Override from base class
	void onChooseFont(HFONT hFont);
};

