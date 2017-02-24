#include "../stdafx.h"
#include "ToolPencil.h"
#include "../Shapes/ShapePencil.h"

ToolPencil::ToolPencil(BitmapChildWindowData* childWindow)
{
	this->childWindowData = childWindow;
}

void ToolPencil::onMouseDown(Point pMouse)
{
	ShapePencil* pencil = new ShapePencil();
	pencil->addPoint(pMouse);
	pencil->setStroke(this->childWindowData->stroke);

	this->childWindowData->addShapeToList(pencil);
}

void ToolPencil::onMouseMove(Point pMouse)
{
	IShape* shape = this->childWindowData->getLastShape();
	if (shape != NULL)
		shape->moveHandleTo(pMouse);
}

void ToolPencil::onMouseUp(Point pMouse)
{

}