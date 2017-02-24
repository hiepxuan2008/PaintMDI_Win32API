// MDI_App.cpp : Defines the entry point for the application.
//
// @Author: Mai Thanh Hiep
// @Student ID: 1312206
// @University of Science

#include "stdafx.h"
#include "MDI_App.h"
#include "WindowController.h"
#include "Commdlg.h"
#include "BitmapChildWindowData.h"
#include "TextChildWindowData.h"

#define MAX_LOADSTRING 100
#define IDM_FIRSTCHILD   50000

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND        hwndMDIClient;

#include "TextFile.h"
#include "BitmapFile.h"

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	FrameWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL  CALLBACK MDICloseProc(HWND, LPARAM);
void OnChooseColor(HWND hWnd);
void OnChooseFont(HWND hWnd);
void CheckMenuItem(HWND hWnd, int iSelItem);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MDI_APP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	MyRegisterClassText(hInstance);
	MyRegisterClassBitmap(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MDI_APP));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hwndMDIClient, &msg) &&
			!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = FrameWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI_APP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	CLIENTCREATESTRUCT clientcreate;
	HWND               hwndChild;
	MDICREATESTRUCT    mdicreate;
	wchar_t buff[100];

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_NEWTEXT:
			wsprintf(buff, L"Text %d", ++WindowController::getInstance()->counterTextWindow);

			mdicreate.szClass = szTextClassName;
			mdicreate.szTitle = buff;
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndChild = (HWND)SendMessage(hwndMDIClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);

			break;
		case ID_FILE_NEWBITMAP:
			wsprintf(buff, L"Bitmap %d", ++WindowController::getInstance()->counterBitmapWindow);

			mdicreate.szClass = szBitmapClassName;
			mdicreate.szTitle = buff;
			mdicreate.hOwner = hInst;
			mdicreate.x = CW_USEDEFAULT;
			mdicreate.y = CW_USEDEFAULT;
			mdicreate.cx = CW_USEDEFAULT;
			mdicreate.cy = CW_USEDEFAULT;
			mdicreate.style = 0;
			mdicreate.lParam = 0;

			hwndChild = (HWND)SendMessage(hwndMDIClient,
				WM_MDICREATE, 0,
				(LPARAM)(LPMDICREATESTRUCT)&mdicreate);
			break;

		case ID_WINDOW_TILEVERTICAL:
			SendMessage(hwndMDIClient, WM_MDITILE,
				MDITILE_VERTICAL, 0L);
			break;
		case ID_WINDOW_TILEHORIZONTAL:
			SendMessage(hwndMDIClient, WM_MDITILE,
				MDITILE_HORIZONTAL, 0L);
			break;
		case ID_WINDOW_CASCADE:
			SendMessage(hwndMDIClient, WM_MDICASCADE,
				0, 0L);
			break;
		case ID_WINDOW_CLOSEALL:
			EnumChildWindows(hwndMDIClient, MDICloseProc, 0L);
			break;

		case ID_FORMAT_CHOOSECOLOR:
			OnChooseColor(hWnd);
			break;
		case ID_FORMAT_CHOSEFONT:
			OnChooseFont(hWnd);
			break;

		case ID_DRAW_PIXEL:
			CheckMenuItem(hWnd, ID_DRAW_PIXEL);
			((BitmapChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->activeTool = DrawToolType::Pencil;
			break;
		case ID_DRAW_LINE:
			CheckMenuItem(hWnd, ID_DRAW_LINE);
			((BitmapChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->activeTool = DrawToolType::Line;
			break;
		case ID_DRAW_ELLIPSE:
			CheckMenuItem(hWnd, ID_DRAW_ELLIPSE);
			((BitmapChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->activeTool = DrawToolType::Ellipse;
			break;
		case ID_DRAW_RECTANGLE:
			CheckMenuItem(hWnd, ID_DRAW_RECTANGLE);
			((BitmapChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->activeTool = DrawToolType::Rectangle;
			break;
		default:
			return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 4);
		clientcreate.idFirstChild = IDM_FIRSTCHILD;

		hwndMDIClient = CreateWindow(L"MDICLIENT", NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			0, 0, 0, 0,
			hWnd,
			(HMENU)NULL,
			hInst,
			(PSTR)&clientcreate);
		ShowWindow(hwndMDIClient, SW_SHOW);
		CheckMenuItem(hWnd, ID_DRAW_PIXEL);

		WindowController::getInstance()->hMenu = GetMenu(hWnd);
		WindowController::getInstance()->hInst = hInst;

	case WM_SIZE:
		UINT w, h;
		// Cập nhật kích thước Client window 
		// theo kích thước frame window
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 0, w, h, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
	}
	return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL  CALLBACK MDICloseProc(HWND hWnd, LPARAM lParam)
{
	SendMessage(hwndMDIClient, WM_MDIDESTROY,
		(WPARAM)hWnd, 0L);

	return 1;
}

void OnChooseColor(HWND hWnd)
{
	CHOOSECOLOR cc;
	static COLORREF acrCustClr[16]; // array of custom colors 
	static DWORD rgbCurrent;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE)
	{
		//Update color
		WindowController::getInstance()->getChildWindowDataOfActiveWindow()->onChooseColor(Color(GetRValue(cc.rgbResult), GetGValue(cc.rgbResult), GetBValue(cc.rgbResult)));
	}
}

void OnChooseFont(HWND hWnd)
{
	CHOOSEFONT cf;
	LOGFONT lf; //Ket qua font duoc chon

	//Init
	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.lpLogFont = &lf;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf))
	{
		HFONT hf = CreateFontIndirect(&lf);
		((TextChildWindowData*)WindowController::getInstance()->getChildWindowDataOfActiveWindow())->onChooseFont(hf);
	}
}

void CheckMenuItem(HWND hWnd, int iSelItem)
{
	//Uncheck all
	CheckMenuItem(GetMenu(hWnd), ID_DRAW_PIXEL, MF_UNCHECKED | MF_BYCOMMAND);
	CheckMenuItem(GetMenu(hWnd), ID_DRAW_LINE, MF_UNCHECKED | MF_BYCOMMAND);
	CheckMenuItem(GetMenu(hWnd), ID_DRAW_RECTANGLE, MF_UNCHECKED | MF_BYCOMMAND);
	CheckMenuItem(GetMenu(hWnd), ID_DRAW_ELLIPSE, MF_UNCHECKED | MF_BYCOMMAND);

	//Check iStelItem
	CheckMenuItem(GetMenu(hWnd), iSelItem, MF_CHECKED | MF_BYCOMMAND);
}