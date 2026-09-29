// Header Files
#include<windows.h>		// This is the most important header file of Win32 SDK

// including our own header file
#include "Window.h"

// Global Declaration of Windows Procedure Callback Function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Thread function declarations 
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
		TEXT("Gaurav WinDev-2026 First Window"),	// window caption bar text
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
	static HANDLE hThread1 = NULL;
	static HANDLE hThread2 = NULL;	

	// code
	switch (iMsg)
	{
	// this is message handler for WM_CREATE msg
	case WM_CREATE:
		/*
			CreateThread(	LPSECURITY_ATTRIBUTES		pointer to STRUCTURE SECURITY_ATTRIBUTES
							SIZE_T						stack size
							LPTHREAD_START_ROUTINE		method name to be created as thread
							LPVOID						long pointer to void* which acts as parameter to thread method
							DWORD						Thread creation flags
							LPDWORD						Thread ID
						)
		*/
		hThread1 = CreateThread(NULL, 
								0,
								(LPTHREAD_START_ROUTINE)ThreadProcOne,
								(LPVOID)hwnd,
								0, 
								NULL);

		hThread2 = CreateThread(NULL,
								0,
								(LPTHREAD_START_ROUTINE)ThreadProcTwo,
								(LPVOID)hwnd,
								0,
								NULL);


		break;
	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("this is message box thread"), TEXT("MessageBox"), MB_OK | MB_ICONINFORMATION);
		break;

	// this is message handler for WM_DESTROY msg
	case WM_DESTROY:
		if (hThread2)
		{
			CloseHandle(hThread2);
			hThread2 = NULL;
		}

		if (hThread1)
		{
			CloseHandle(hThread1);
			hThread1 = NULL;
		}

		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// Forward the message to Default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// ThreadProdOne
DWORD WINAPI ThreadProcOne(LPVOID param)
{
	// variable declarations 
	HDC hdc = NULL;
	INT i = 0;
	TCHAR str[255];

	// code
	hdc = GetDC((HWND)param);

	// set background color of text to black color
	SetBkColor(hdc, RGB(0, 0, 0));

	// set the text color to green 
	SetTextColor(hdc, RGB(0, 255, 0));

	// incrementing loop
	for (i = 0; i <= INT_MAX; i++)
	{
		wsprintf(str, TEXT("Incrementing : %d"), i);
		TextOut(hdc, 5, 10, str, wcslen(str));
	}

	if (hdc)
	{
		ReleaseDC((HWND)param, hdc);
		hdc = NULL;
	}

	return 0;
}

// ThreadProdTwo
DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	// variable declarations 
	HDC hdc = NULL;
	INT i = 0;
	TCHAR str[255];

	// code
	hdc = GetDC((HWND)param);

	// set background color of text to black color
	SetBkColor(hdc, RGB(0, 0, 0));

	// set the text color to green 
	SetTextColor(hdc, RGB(255, 0, 0));

	// decrementing loop
	for (i = INT_MAX; i >= 0; i--)
	{
		wsprintf(str, TEXT("Decrementing : %d"), i);
		TextOut(hdc, 5, 30, str, wcslen(str));
	}

	if (hdc)
	{
		ReleaseDC((HWND)param, hdc);
		hdc = NULL;
	}

	return 0;
}

/*

Remind Mam to tell about why message box is not supposed to add in 
WM_SIZE and WM_PAINT and WM_MOUSEMOVE during DLL lecture. 

*/