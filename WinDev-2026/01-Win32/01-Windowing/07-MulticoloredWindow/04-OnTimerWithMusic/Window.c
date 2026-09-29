// Header Files
#include<windows.h>		// This is the most important header file of Win32 SDK

// including our own header file
#include "Window.h"

// TIMER STEP 0: Declaring my own timer
#define GCS_TIMER 201

// winmm.lib is the library to be linked to play a sound
// Alternatively, can also winmm.lib in build.bat in link.exe command line
#pragma comment(lib, "winmm.lib")

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

	// structure to rectangle 
	RECT rect;
	// handle to device context (painter) 
	HDC hdc = NULL;
	// structure to paint 
	PAINTSTRUCT ps;
	static unsigned int iColorFlag = 0;
	HBRUSH hBrush = NULL;

	// code
	switch (iMsg)
	{
	case WM_CREATE:			// this is message handler for WM_CREATE msg
		// TIMER STEP 1: set the timer for appropriate time. 
		SetTimer(hwnd, GCS_TIMER, 1000, NULL);	// 1000 ms means 1 second
		PlaySound(MAKEINTRESOURCE(GCS_BIRTHDAY_MUSIC), GetModuleHandle(NULL), SND_LOOP | SND_ASYNC | SND_RESOURCE);
		break;
	case WM_PAINT:			// this is message handler for WM_PAINT msg
		// zero-out the RECT structure
		ZeroMemory((void*)&rect, sizeof(RECT));

		// get the client area rectangle of your window 
		GetClientRect(hwnd, &rect);

		// zero-out the PAINTSTRUCT structure
		ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));

		// get the painter to paint for your window
		hdc = BeginPaint(hwnd, &ps);

		// create brush of desired color
		switch (iColorFlag)
		{
		// Red color
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		// Green color
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		// Blue color
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		// Cyan color
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		// Magenta color
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		// Yellow color
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		// Orange color
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 128, 0));
			break;
		// Violet color
		case 8:
			hBrush = CreateSolidBrush(RGB(128, 128, 255));
			break;
		// White color
		case 9:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		// Black color
		default:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		}

		// Give this newly created brush to the painter hdc (select this new brush)
		SelectObject(hdc, hBrush);

		// Now, fill the client area rectangle with the selected brush color
		FillRect(hdc, &rect, hBrush);

		// Now delete the brush
		if (hBrush)
		{
			DeleteObject(hBrush);
			hBrush = NULL;
		}

		// release the painter 
		if (hdc)
		{
			EndPaint(hwnd, &ps);
			hdc = NULL;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		default:
			break;
		}
		break;
	// TIMER STEP 2: When the appropriate time ends, you'll receive the WM_TIMER msg. This is just like the irritating alarm bell
	case WM_TIMER:
		// TIMER STEP 3: Kill the timer. 
		KillTimer(hwnd, GCS_TIMER);

		// TIMER STEP 4: Do the necessary work for which the timer was set. 
		iColorFlag++;

		// if iColorFlag exceeds value beyond 9, reset the flag
		if (iColorFlag > 9)
			iColorFlag = 0;
		
		// Now explictly call WM_PAINT for the pressed character key
		// This method POSTS WM_PAINT
		InvalidateRect(hwnd, NULL, TRUE);

		// TIMER STEP 5: Reset the timer for the next WM_TIMER msg. 
		SetTimer(hwnd, GCS_TIMER, 1000, NULL);
		break;
	case WM_DESTROY:		// this is message handler for WM_DESTROY msg
		// Stop playing the music
		PlaySound(NULL, NULL, 0);
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// Forward the message to Default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

/*
Q. 8 cases when repainting must be done for window?
1. When window is first ever created
2. When another window was overlapping with your window is now uncovering your window
3. When system menu is now uncovering your window
4. When icon is moved across your window
5. When mouse cursor is moved across your window
6. When another window is moved across your window OR your own window is moved
7. When your own window is resized
8. When scrolling is done


HDC - part of gdi32.dll

Remind Mam to tell about why message box is not supposed to add in 
WM_SIZE and WM_PAINT and WM_MOUSEMOVE during DLL lecture. 

===============================================================

0. Declare your timer. 
1. When your application starts running, set the timer for appropriate time. 
2. When that appropriate time has passed, you'll receive the WM_TIMER msg. This is just like the irritating alarm bell. 
3. Inside WM_TIMER msg handler, kill the timer. 
4. Do the necessary work for which the timer was set. 
5. Reset the timer for the next WM_TIMER msg. 
6. Go to step 2. 

HW - 
background - black
text - white
on key press, color of text should change
on mouse click, change the text

09-Multicolored text
*/