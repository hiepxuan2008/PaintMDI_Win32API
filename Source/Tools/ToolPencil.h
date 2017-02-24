#pragma once
#include "ITool.h"

class ToolPencil : public ITool
{
public:
	ToolPencil(BitmapChildWindowData* childWindow);
public:
	void onMouseDown(Point pMouse);
	void onMouseMove(Point pMouse);
	void onMouseUp(Point pMouse);
};

