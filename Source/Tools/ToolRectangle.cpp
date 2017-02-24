#include "../stdafx.h"
#include "ToolRectangle.h"
#include "../Shapes/ShapeRectangle.h"

ToolRectangle::ToolRectangle(BitmapChildWindowData* childWindow)
{
	this->childWindowData = childWindow;
}

void ToolRectangle::onMouseDown(Point pMouse)
{
	ShapeRectangle* rect = new ShapeRectangle(pMouse.x, pMouse.y, pMouse.x, pMouse.y);
	rect->setStroke(this->childWindowData->stroke);

	this->childWindowData->addShapeToList(rect);
}

void ToolRectangle::onMouseMove(Point pMouse)
{
	IShape* shape = this->childWindowData->getLastShape();
	if (shape != NULL)
		shape->moveHandleTo(pMouse);
}

void ToolRectangle::onMouseUp(Point pMouse)
{

}