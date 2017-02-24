#pragma once
#include "stdafx.h"
#include "ChildWindowData.h"

//Singleton Pattern
class WindowController
{
public:
	HMENU		hMenu;
	HINSTANCE hInst;
	HWND hActiveChildWindow; //Current Active Child Window
	int counterBitmapWindow; //Counter of Bitmap window
	int counterTextWindow; //Counter of text window

public:
	ChildWindowData* getChildWindowDataOfActiveWindow();

public:
	static WindowController* getInstance();
	~WindowController();

private:
	WindowController();
};