#include "TextFile.h"
#include "WindowController.h"
#include "MDI_App.h"
#include "TextChildWindowData.h"

//Implementations
LRESULT CALLBACK	TextProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;
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
	case WM_CREATE:
	{
					  HWND hEditWnd;
					  hEditWnd = CreateWindowEx(0, L"Edit", NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE, 0, 0, 0, 0, hWnd, NULL, WindowController::getInstance()->hInst, NULL);
					  ShowWindow(hEditWnd, SW_NORMAL);

					  //Store to cbWndExtra
					  TextChildWindowData* windowData = new TextChildWindowData;
					  windowData->hEdit = hEditWnd;
					  windowData->hOwnerWnd = hWnd;
					  SetWindowLong(hWnd, 0, (LONG)windowData);
					  break;
	}
	case WM_SIZE:
	{
					TextChildWindowData* windowData = (TextChildWindowData*)GetWindowLong(hWnd, 0);
					MoveWindow(windowData->hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), 0);
					break;
	}
	case WM_CTLCOLOREDIT:
	{
							Color color = ((TextChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->color;
							SetTextColor((HDC)wParam, RGB(color.r, color.g, color.b));
							break;
	}
	case WM_MDIACTIVATE:
		WindowController::getInstance()->hActiveChildWindow = hWnd;
		hMenu = WindowController::getInstance()->hMenu;
		//Disable all Edit Menu Items
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
			EnableMenuItem(hMenu, ID_EDIT_COPY, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_EDIT_CUT, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_EDIT_PASTE, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_EDIT_SELECTALL, MF_ENABLED | MF_BYCOMMAND);

			//Enable Choose Font Menu Item
			EnableMenuItem(hMenu, ID_FORMAT_CHOSEFONT, MF_ENABLED | MF_BYCOMMAND);
		}

		break;
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM MyRegisterClassText(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TextProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 4;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI_APP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szTextClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}