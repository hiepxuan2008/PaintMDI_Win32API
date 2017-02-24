#include "ShapeEllipse.h"

ShapeEllipse::ShapeEllipse(int iLeft, int iTop, int iRight, int iBottom) : _iLeft(iLeft), _iTop(iTop), _iRight(iRight), _iBottom(iBottom)
{
}

void ShapeEllipse::moveHandleTo(Point pMouse)
{
	_iRight = pMouse.x;
	_iBottom = pMouse.y;
}

void ShapeEllipse::draw(HDC hdc)
{
	HPEN hPen = CreatePen(_stroke.style, _stroke.width, RGB(_stroke.color.r, _stroke.color.g, _stroke.color.b));

	SelectObject(hdc, hPen);
	Ellipse(hdc, _iLeft, _iTop, _iRight, _iBottom);
	DeleteObject(hPen);
}