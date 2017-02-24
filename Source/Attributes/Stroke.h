#pragma once
#include "../stdafx.h"
#include "Color.h"

struct Stroke
{
	Color color;
	int width;
	int style;

	Stroke() : color(0, 0, 0), width(5), style(PS_SOLID){}
};