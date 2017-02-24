#pragma once
#include "ChildWindowData.h"

#include <list>
#include <vector>
#include "Shapes/IShape.h"
#include "Tools/ITool.h"
#include "Attributes/Attributes.h"
enum class DrawToolType { Pencil, Line, Rectangle, Ellipse, None };

class ITool;

class BitmapChildWindowData : public ChildWindowData
{
public:
	BitmapChildWindowData();
	~BitmapChildWindowData();

public:
	Stroke stroke; //Current Stroke
	DrawToolType activeTool; //Active Tool
public:
	void onChooseColor(Color color); //Override from base class

public:
	void addShapeToList(IShape* shape);
	void draw(HDC hdc);

	IShape* getLastShape();
	ITool* getCurrentTool();

private:
	std::list<IShape*>* shapes;
	std::vector<ITool*>* tools;
};