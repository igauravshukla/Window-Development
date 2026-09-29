// Header Files
#include<windows.h>		// This is the most important header file of Win32 SDK

#include "MyMathTwo.h"

// including our own header file
#include "Window.h"

// Global Declaration of Windows Procedure Callback Function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX myWindowClass;									// structure 
	TCHAR szMyWindowClassName[] = TEXT("Gaurav's Window");
	HWND hwnd = NULL;
	MSG msg;													// structure

	// code

	// initializing our Window Class
	ZeroMemory((void*)&myWindowClass, sizeof(WNDCLASSEX));
	// instead of ZeroMemory, we can use memset() as follows:
	//memset((void*)&myWindowClass, 0, sizeof(WNDCLASSEX));

	// cbSize - count of bytes of size of this structure (size of structure in bytes)
	myWindowClass.cbSize = sizeof(WNDCLASSEX);

	// CS stands for class style
	// if resize the window (horizontally / vertically), redraw the window
	myWindowClass.style = CS_HREDRAW | CS_VREDRAW;

	// extra information about this window class
	myWindowClass.cbClsExtra = 0;

	// extra information about one window of this window class
	myWindowClass.cbWndExtra = 0;

	// long pointer to Window Procedure function (callback method)
	// this is registering the callback function 
	myWindowClass.lpfnWndProc = WndProc;

	// long pointer to zero terminated string which is class name
	myWindowClass.lpszClassName = szMyWindowClassName;

	// long pointer to zero terminated string which is menu name
	// as of now there is no menu to our window, hence null
	myWindowClass.lpszMenuName = NULL;

	// handle to brush which used to color the background of the window
	myWindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// handle of the instance of this process 
	myWindowClass.hInstance = hInstance;

	// handle to cursor 
	myWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// handle to large icon 
	myWindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(GCS_ICON));

	// handle to small icon (list view)
	myWindowClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(GCS_ICON));

	// Register the above Window class
	RegisterClassEx(&myWindowClass);

	// Create the Window IN MEMORY ONLY 
	hwnd = CreateWindow(szMyWindowClassName,		// class name 
		TEXT("Gaurav WindDev-2026  First Window"),	// window caption bar text
		WS_OVERLAPPEDWINDOW,						// window style 
		CW_USEDEFAULT,								// window top left x co-ordinate 
		CW_USEDEFAULT,								// window top left y co-ordinate 
		CW_USEDEFAULT,								// width of the window 
		CW_USEDEFAULT,								// height of the window 
		NULL,										// handle to parent window of this window (NULL means not known)
		NULL,										// handle to menu of this window (NULL means not having anything)
		hInstance,									// handle of the process instance which is hosting this window 
		NULL);										// ??

	// Show the Window on desktop 
	ShowWindow(hwnd, SW_SHOWDEFAULT);

	// Update the Window (color the background) 
	UpdateWindow(hwnd);

	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Translate or simplify the Message
		TranslateMessage(&msg);

		// Dispatch or post the message to WndProc()
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

// Defining Window Procedure Callback Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// variable declarations 
	int num = 1216;
	int cube = 0;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:			// WM_CREATE Message Handler
		cube = MakeCube(num);
		wsprintf(str, TEXT("Cube of %d is %d"), num, cube);
		MessageBox(	hwnd,
					str,
					TEXT("Cube"),
					MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:		// WM_DESTROY Message Handler
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// Forward the message to Default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
