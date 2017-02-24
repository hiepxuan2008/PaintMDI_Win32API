#pragma once
#include "../Attributes/Attributes.h"

//Abstract class
class IShape
{
protected:
	Stroke _stroke;

public:
	virtual void draw(HDC hdc) = 0;
	virtual void moveHandleTo(Point pMouse) = 0;

	void setStroke(Stroke stroke);
	IShape();
	~IShape();
};

