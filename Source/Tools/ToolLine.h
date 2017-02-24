#pragma once
#include "ITool.h"

class ToolLine : public ITool
{
public:
	ToolLine(BitmapChildWindowData* childWindow);
public:
	void onMouseDown(Point pMouse);
	void onMouseMove(Point pMouse);
	void onMouseUp(Point pMouse);
};

