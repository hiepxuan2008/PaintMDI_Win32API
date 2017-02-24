#include "BitmapFile.h"
#include "MDI_App.h"
#include "BitmapChildWindowData.h"
#include "WindowController.h"
#include "stdafx.h"

//Implementations
LRESULT CALLBACK	BitmapProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU hMenu;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		default:
			return DefMDIChildProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
					  BitmapChildWindowData* windowData = new BitmapChildWindowData;
					  SetWindowLong(hWnd, 0, (LONG)windowData);
					  break;
	}
	case WM_MDIACTIVATE:
		WindowController::getInstance()->hActiveChildWindow = hWnd;
		//Disable all Edit Menu Items
		hMenu = WindowController::getInstance()->hMenu;
		EnableMenuItem(hMenu, ID_EDIT_COPY, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_EDIT_CUT, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_EDIT_PASTE, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_EDIT_SELECTALL, MF_GRAYED | MF_BYCOMMAND);
		//Disable all Draw Menu Items
		EnableMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_DRAW_PIXEL, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_DRAW_LINE, MF_GRAYED | MF_BYCOMMAND);

		if (lParam == (LPARAM)hWnd)
		{
			//Enable Draw Menu Items
			EnableMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_DRAW_PIXEL, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_DRAW_LINE, MF_ENABLED | MF_BYCOMMAND);

			//Disable Choose Font Menu Item
			EnableMenuItem(hMenu, ID_FORMAT_CHOSEFONT, MF_GRAYED | MF_BYCOMMAND);
		}
	case WM_LBUTTONDOWN:
		OnLButtonDown(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
	{
					 //Handle device context
					 hdc = BeginPaint(hWnd, &ps);

					 //Client region
					 RECT rect;
					 GetClientRect(hWnd, &rect);
					 int nWidth = rect.right - rect.left;
					 int nHeight = rect.bottom - rect.top;

					 //Create memory device context
					 HDC hMemDC = CreateCompatibleDC(hdc);
					 HBITMAP hBmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);

					 //Select new object
					 HGDIOBJ hOldBmp = SelectObject(hMemDC, hBmp);

					 //Set to background color to white
					 FillRect(hMemDC, &rect, HBRUSH(GetStockObject(WHITE_BRUSH)));

					 //Draw shapes
					 BitmapChildWindowData* windowData = (BitmapChildWindowData*)GetWindowLong(hWnd, 0);
					 windowData->draw(hMemDC);

					 //Transfer color data from source device context to destinate device context
					 BitBlt(hdc, 0, 0, nWidth, nHeight, hMemDC, 0, 0, SRCCOPY);

					 //Recover the old object
					 SelectObject(hMemDC, hOldBmp);

					 //Clean memory
					 DeleteObject(hBmp);
					 DeleteDC(hMemDC);

					 EndPaint(hWnd, &ps);
					 break;
	}
		
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM MyRegisterClassBitmap(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BitmapProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 4; //4 bytes point to WindowData object
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI_APP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szBitmapClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	x = LOWORD(lParam);
	y = HIWORD(lParam);

	BitmapChildWindowData* windowData = (BitmapChildWindowData*)GetWindowLong(hWnd, 0);
	windowData->getCurrentTool()->onMouseDown(Point(x, y));

	//Redraw the client area
	RECT hRect;
	GetClientRect(hWnd, &hRect);
	InvalidateRect(hWnd, &hRect, false);
}

void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (!(wParam & MK_LBUTTON))
		return;

	int x, y;
	x = LOWORD(lParam);
	y = HIWORD(lParam);

	BitmapChildWindowData* windowData = (BitmapChildWindowData*)GetWindowLong(hWnd, 0);
	windowData->getCurrentTool()->onMouseMove(Point(x, y));

	//Redraw the client area
	RECT hRect;
	GetClientRect(hWnd, &hRect);
	InvalidateRect(hWnd, &hRect, false);
}