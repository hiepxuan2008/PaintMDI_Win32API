#include "stdafx.h"
#include "WindowController.h"

WindowController::WindowController()
{
	counterTextWindow = 0;
	counterBitmapWindow = 0;
	hActiveChildWindow = NULL;
}

WindowController::~WindowController()
{

}

ChildWindowData* WindowController::getChildWindowDataOfActiveWindow()
{
	if (hActiveChildWindow == NULL)
		return NULL;

	return (ChildWindowData*)GetWindowLong(hActiveChildWindow, 0);
}

WindowController* WindowController::getInstance()
{
	static WindowController* _instance = new WindowController();

	return _instance;
}