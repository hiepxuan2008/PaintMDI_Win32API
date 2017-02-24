#pragma once
#include "../Attributes/Point.h"
#include "../BitmapChildWindowData.h"

class BitmapChildWindowData;

//Abstract class
class ITool
{
protected:
	BitmapChildWindowData* childWindowData;
public:
	virtual void onMouseDown(Point pMouse) = 0;
	virtual void onMouseMove(Point pMouse) = 0;
	virtual void onMouseUp(Point pMouse) = 0;
};