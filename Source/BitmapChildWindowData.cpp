#include "stdafx.h"
#include "BitmapChildWindowData.h"
#include "Shapes/Shapes.h"
#include "Tools/Tools.h"

BitmapChildWindowData::BitmapChildWindowData()
{
	activeTool = DrawToolType::Pencil;
	shapes = new std::list<IShape*>();
	tools = new std::vector<ITool*>();
	tools->push_back(new ToolPencil(this));
	tools->push_back(new ToolLine(this));
	tools->push_back(new ToolRectangle(this));
	tools->push_back(new ToolEllipse(this));
}


BitmapChildWindowData::~BitmapChildWindowData()
{
	//Delete tool objects
	for (int i = 0; i < (int)tools->size(); ++i)
		delete tools->at(i);
	delete tools;

	//Delete shape objects
	for (std::list<IShape*>::iterator it = shapes->begin(); it != shapes->end(); ++it)
	{
		delete *it;
	}
	delete shapes;
}

void BitmapChildWindowData::onChooseColor(Color color) //Override from base class
{
	this->stroke.color = color;
}

void BitmapChildWindowData::addShapeToList(IShape* shape)
{
	shapes->push_front(shape);
}

IShape* BitmapChildWindowData::getLastShape()
{
	std::list<IShape*>::iterator it = shapes->begin();
	if (it == shapes->end()) //If no shape in list then return
		return NULL;

	return (*it);
}

void BitmapChildWindowData::draw(HDC hdc)
{
	for (std::list<IShape*>::reverse_iterator rit = shapes->rbegin(); rit != shapes->rend(); ++rit)
	{
		(*rit)->draw(hdc);
	}
}

ITool* BitmapChildWindowData::getCurrentTool()
{
	/*if ((int)ActiveTool >= 0 && (int)ActiveTool < tools->size())
	return tools[(int)ActiveTool];*/

	return tools->at(int(activeTool));
}