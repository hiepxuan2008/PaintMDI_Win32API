#pragma once
#include "ITool.h"
class ToolEllipse : public ITool
{
public:
	ToolEllipse(BitmapChildWindowData* childWindow);
public:
	void onMouseDown(Point pMouse);
	void onMouseMove(Point pMouse);
	void onMouseUp(Point pMouse);
};

