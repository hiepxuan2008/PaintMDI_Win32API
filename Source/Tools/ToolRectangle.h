#pragma once
#include "ITool.h"
class ToolRectangle : public ITool
{
public:
	ToolRectangle(BitmapChildWindowData* childWindow);
public:
	void onMouseDown(Point pMouse);
	void onMouseMove(Point pMouse);
	void onMouseUp(Point pMouse);
};

