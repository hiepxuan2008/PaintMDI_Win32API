#include "ShapePencil.h"

ShapePencil::ShapePencil()
{
	_points = new std::vector<Point>;
}

ShapePencil::~ShapePencil()
{
}

void ShapePencil::addPoint(Point point)
{
	_points->push_back(point);
}

void ShapePencil::moveHandleTo(Point pMouse)
{
	_points->push_back(pMouse);
}

void ShapePencil::draw(HDC hdc)
{
	HPEN hPen = CreatePen(_stroke.style, _stroke.width, RGB(_stroke.color.r, _stroke.color.g, _stroke.color.b));

	SelectObject(hdc, hPen);
	
	//Draw all points
	if (_points->size() > 0) //Draw first point
	{
		MoveToEx(hdc, _points->at(0).x, _points->at(0).y, NULL);
		LineTo(hdc, _points->at(0).x, _points->at(0).y);
	}
	for (int i = 0; i < (int)_points->size() - 1; ++i) //Draw others line
	{
		MoveToEx(hdc, _points->at(i).x, _points->at(i).y, NULL);
		LineTo(hdc, _points->at(i + 1).x, _points->at(i + 1).y);
	}

	DeleteObject(hPen);
}