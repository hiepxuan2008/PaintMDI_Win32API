#include "IShape.h"
#include "../stdafx.h"

IShape::IShape()
{
}

IShape::~IShape()
{
}

void IShape::setStroke(Stroke stroke)
{
	this->_stroke = stroke;
}