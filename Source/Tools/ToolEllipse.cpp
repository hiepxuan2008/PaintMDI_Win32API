#include "ToolEllipse.h"
#include "../Shapes/ShapeEllipse.h"

ToolEllipse::ToolEllipse(BitmapChildWindowData* childWindow)
{
	this->childWindowData = childWindow;
}

void ToolEllipse::onMouseDown(Point pMouse)
{
	ShapeEllipse* ellipse = new ShapeEllipse(pMouse.x, pMouse.y, pMouse.x, pMouse.y);
	ellipse->setStroke(this->childWindowData->stroke);

	this->childWindowData->addShapeToList(ellipse);
}

void ToolEllipse::onMouseMove(Point pMouse)
{
	IShape* shape = this->childWindowData->getLastShape();
	if (shape != NULL)
		shape->moveHandleTo(pMouse);
}

void ToolEllipse::onMouseUp(Point pMouse)
{

}