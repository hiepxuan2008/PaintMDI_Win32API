#pragma once
#include "stdafx.h"

#define szTextClassName L"TextClass";

//Prototype
LRESULT CALLBACK	TextProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClassText(HINSTANCE hInstance);

