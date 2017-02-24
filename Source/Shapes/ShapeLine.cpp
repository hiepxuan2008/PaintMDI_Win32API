#include "ShapeLine.h"

ShapeLine::ShapeLine()
{
}

ShapeLine::~ShapeLine()
{
}

ShapeLine::ShapeLine(Point pStart, Point pEnd) : _pStart(pStart), _pEnd(pEnd)
{

}

ShapeLine::ShapeLine(Point pStart, Point pEnd, Stroke stroke) : _pStart(pStart), _pEnd(pEnd)
{
	this->_stroke = stroke;
}

void ShapeLine::moveHandleTo(Point pMouse)
{
	_pEnd = pMouse;
}

void ShapeLine::draw(HDC hdc)
{
	HPEN hPen = CreatePen(_stroke.style, _stroke.width, RGB(_stroke.color.r, _stroke.color.g, _stroke.color.b));

	SelectObject(hdc, hPen);
	MoveToEx(hdc, _pStart.x, _pStart.y, NULL);
	LineTo(hdc, _pEnd.x, _pEnd.y);
	DeleteObject(hPen);
}