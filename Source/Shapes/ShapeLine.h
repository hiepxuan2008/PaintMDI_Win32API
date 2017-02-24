#pragma once
#include "IShape.h"

class ShapeLine : public IShape
{
private:
	Point _pStart;
	Point _pEnd;

public:
	ShapeLine();
	ShapeLine(Point pStart, Point pEnd);
	ShapeLine(Point pStart, Point pEnd, Stroke stroke);
	void moveHandleTo(Point pMouse);
	void draw(HDC hdc);

	~ShapeLine();
};

