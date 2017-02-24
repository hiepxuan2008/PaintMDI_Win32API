#pragma once
#include <vector>
#include "IShape.h"

class ShapePencil : public IShape
{
private:
	std::vector<Point>* _points;

public:
	ShapePencil();
	void addPoint(Point point);
	void moveHandleTo(Point pMouse);
	void draw(HDC hdc);

	~ShapePencil();
};

