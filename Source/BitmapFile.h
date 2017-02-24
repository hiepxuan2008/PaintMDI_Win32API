#pragma once
#include "stdafx.h"

#define szBitmapClassName L"BitmapClass";

//Prototype
LRESULT CALLBACK	BitmapProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClassBitmap(HINSTANCE hInstance);

void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
//void OnChooseColor(HWND hWnd);