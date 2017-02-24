#include "../stdafx.h"
#include "ToolLine.h"
#include "../Shapes/ShapeLine.h"

ToolLine::ToolLine(BitmapChildWindowData* childWindow)
{
	this->childWindowData = childWindow;
}

void ToolLine::onMouseDown(Point pMouse)
{
	ShapeLine* line = new ShapeLine(pMouse, pMouse, this->childWindowData->stroke);

	this->childWindowData->addShapeToList(line);
}

void ToolLine::onMouseMove(Point pMouse)
{
	IShape* shape = this->childWindowData->getLastShape();
	if (shape != NULL)
		shape->moveHandleTo(pMouse);
}

void ToolLine::onMouseUp(Point pMouse)
{

}