#pragma once
#include "Attributes/Attributes.h"
enum class WindowType { Text, Bitmap };

class ChildWindowData
{
protected:
	WindowType windowType;
public:
	virtual void onChooseColor(Color color) = 0;
};