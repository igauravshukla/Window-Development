// Header Files
#include<windows.h>		// This is the most important header file of Win32 SDK

// including our own header file
#include "Window.h"

// winmm.lib is the library to be linked to play a sound
// Alternatively, can also winmm.lib in build.bat in link.exe command line
#pragma comment(lib, "winmm.lib")

// TIMER STEP 0: Declaring my own timer
#define GCS_TIMER 201

// Defining circle radius as constant
#define CIRCLE_RADIUS 100

#define ANIMATION_DELTA	5

// Define constant colors
#define BACKGROUND_LAVENDER_COLOR	RGB(128, 128, 255)
#define CIRCLE_LEMON_YELLOW_COLOR	RGB(255, 244, 79)
#define TEXT_BLACK_COLOR			RGB(0, 0, 0)

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
	ShowWindow(hwnd, SW_MAXIMIZE);

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
	static RECT WindowRect;
	// handle to device context (painter) 
	static HDC hdc = NULL;
	// structure to paint 
	PAINTSTRUCT ps;

	HBRUSH hBrush_Background = NULL;
	HBRUSH hBrush_Circle = NULL;

	static unsigned int windowWidth = 0;
	static unsigned int windowHeight = 0;

	static unsigned int circleCenterX = 0;
	static unsigned int circleCenterY = 0;

	unsigned int clickXCoord = 0;
	unsigned int clickYCoord = 0;

	static RECT circleRect;

	// boolean variable to check if sound is ON or OFF
	static BOOL bSoundOn = FALSE;

	// boolean variable to check if MOUSE pointer should be catch
	static BOOL bMoveCircleWithMousePointer = FALSE;

	static BOOL bAnimate = FALSE;

	static BOOL bAnimateCircleTowardsRight = TRUE;

	TCHAR str[] = TEXT("Happy Birthday WIN32!!!");

	// code
	switch (iMsg)
	{
	// this is message handler for WM_CREATE msg
	case WM_CREATE:
		break;

	// this is message handler for WM_PAINT msg
	case WM_PAINT:
		// zero-out the PAINTSTRUCT structure
		ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));

		// get the painter to paint for your window
		hdc = BeginPaint(hwnd, &ps);

		// color the client area background with violet color
		hBrush_Background = CreateSolidBrush(BACKGROUND_LAVENDER_COLOR);

		// Give this newly created background brush to the painter hdc (select this new brush)
		SelectObject(hdc, hBrush_Background);

		// Now, fill the client area rectangle with the selected brush color
		FillRect(hdc, &WindowRect, hBrush_Background);

		// Draw lemon yellow colored circle
		hBrush_Circle = CreateSolidBrush(CIRCLE_LEMON_YELLOW_COLOR);

		// Give this newly created circle brush to the painter hdc (select this new brush)
		SelectObject(hdc, hBrush_Circle);

		// Animation logic
		if (bAnimate == TRUE)		// execute this block when animation is enabled 
		{
			if (bAnimateCircleTowardsRight == TRUE)		// animate circle towards right
			{
				if (circleCenterX <= (WindowRect.right - CIRCLE_RADIUS))
					circleCenterX = circleCenterX + ANIMATION_DELTA;
				else
					bAnimateCircleTowardsRight = FALSE;	// stop animation towards right
			}
			else										// animate circle towards left
			{
				if (circleCenterX >= WindowRect.left + CIRCLE_RADIUS)
					circleCenterX = circleCenterX - ANIMATION_DELTA;
				else
					bAnimateCircleTowardsRight = TRUE;
			}
		}
		ZeroMemory((void*)&circleRect, sizeof(RECT));
		circleRect.left = circleCenterX - CIRCLE_RADIUS;
		circleRect.top = circleCenterY - CIRCLE_RADIUS;
		circleRect.right = circleCenterX + CIRCLE_RADIUS;
		circleRect.bottom = circleCenterY + CIRCLE_RADIUS;

		Ellipse(hdc, circleRect.left, circleRect.top, circleRect.right, circleRect.bottom);

		// now draw the text inside the circle
		SetTextColor(hdc, TEXT_BLACK_COLOR);

		// set background color of text to lemon yellow color
		SetBkColor(hdc, CIRCLE_LEMON_YELLOW_COLOR);

		// draw the text 
		// DrawText(who, what, how much, where, how)
		DrawText(hdc, str, -1, &circleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// Now delete the brush for circle
		if (hBrush_Circle)
		{
			DeleteObject(hBrush_Circle);
			hBrush_Circle = NULL;
		}

		// Now delete the brush for background
		if (hBrush_Background)
		{
			DeleteObject(hBrush_Background);
			hBrush_Background = NULL;
		}

		// release the painter 
		if (hdc)
		{
			EndPaint(hwnd, &ps);
			hdc = NULL;
		}
		break;

	case WM_SIZE:
		// zero-out the RECT structure
		ZeroMemory((void*)&WindowRect, sizeof(RECT));

		// get the client area rectangle of your window 
		GetClientRect(hwnd, &WindowRect);

		windowWidth = WindowRect.right - WindowRect.left;
		windowHeight = WindowRect.bottom - WindowRect.top;

		// set center of window as center of circle
		circleCenterX = windowWidth / 2;
		circleCenterY = windowHeight / 2;
		break;

	case WM_MOUSEMOVE:
		if (bMoveCircleWithMousePointer == TRUE)
		{
			circleCenterX = LOWORD(lParam);
			circleCenterY = HIWORD(lParam);

			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;

	case WM_LBUTTONDOWN:
		if (bMoveCircleWithMousePointer == FALSE)
		{
			clickXCoord = LOWORD(lParam);	// x-co-ordinate of window where left mouse button is pressed
			clickYCoord = HIWORD(lParam);	// y-co-ordinate of window where left mouse button is pressed
			if (GetPixel(hdc, clickXCoord, clickYCoord) == CIRCLE_LEMON_YELLOW_COLOR)
			{
				MessageBox(	hwnd,
							TEXT("You've clicked inside the birthday circle"),
							TEXT("Surpise Message"),
							MB_OK | MB_ICONINFORMATION);
			}
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

	case WM_CHAR:
		switch (wParam)
		{
		// toggling animation
		case 'A':
		case 'a':
			bMoveCircleWithMousePointer = FALSE;
			if (bAnimate == FALSE)
			{
				// TIMER STEP 1: set the timer for appropriate time. 
				SetTimer(hwnd, GCS_TIMER, 100, NULL);	// 100 ms means 0.1 second
				bAnimate = TRUE;
			}
			else if (bAnimate == TRUE)
			{
				// TIMER STEP 3: Kill the timer. 
				KillTimer(hwnd, GCS_TIMER);
				bAnimate = FALSE;
			}
			break;

		// Recenter circle position
		case 'C':
		case 'c':
			// set center of window as center of circle
			bMoveCircleWithMousePointer = FALSE;
			bAnimate = FALSE;
			circleCenterX = windowWidth / 2;
			circleCenterY = windowHeight / 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		// Toggle circle movement with mouse
		case 'M':
		case 'm':
			bAnimate = FALSE;
			if (bMoveCircleWithMousePointer == TRUE)
			{
				bMoveCircleWithMousePointer = FALSE;
			}
			else if (bMoveCircleWithMousePointer == FALSE)
			{
				bMoveCircleWithMousePointer = TRUE;
			}
			break;

		// Toggle music ON/OFF
		case 'S':
		case 's':
			if (bSoundOn == TRUE)
			{
				// Stop playing the music
				PlaySound(NULL, NULL, 0);
				bSoundOn = FALSE;
			}
			else if (bSoundOn == FALSE)
			{
				PlaySound(MAKEINTRESOURCE(GCS_BIRTHDAY_MUSIC), GetModuleHandle(NULL), SND_LOOP | SND_ASYNC | SND_RESOURCE);
				bSoundOn = TRUE;
			}
			break;

		default:
			break;
		}

	// TIMER STEP 2: When the appropriate time ends, you'll receive the WM_TIMER msg. This is just like the irritating alarm bell
	case WM_TIMER:
		if (bAnimate == TRUE)
		{
			// TIMER STEP 3: Kill the timer. 
			KillTimer(hwnd, GCS_TIMER);

			// Now explictly call WM_PAINT for the pressed character key
			// This method POSTS WM_PAINT
			InvalidateRect(hwnd, NULL, TRUE);

			// TIMER STEP 5: Reset the timer for the next WM_TIMER msg. 
			SetTimer(hwnd, GCS_TIMER, 100, NULL);
		}
		break;

	// this is message handler for WM_DESTROY msg
	case WM_DESTROY:
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

===============================================================

Task 1: 
	On 's' key press, music should be on and again on 's' key press, music should be off.
	Music should not start on window start

Task 2:
	Create a circle using Ellipse with all size same. 
	Circle should always be at center. 

	Solution:
		Center of window == center of circle 
		Center of window	= (X,Y)
							= ((window width / 2),(window height / 2))
							= 

Assignment:
	1. This should work when mouse movement is OFF. bMoveCircleWithMousePointer == FALSE
	2. When clicked (left mouse button down) inside the circle, then only message box should come. 
	Caption - Surpise Message
	Text - You've clicked inside the birthday circle
	Hint - GetPixel()

For flickering effect,
1. WM_ERASEBKGND
2. How double buffering is done in Win32?

A -> H - if animation is true, horizontal animation 
A -> V - if animation is true, vertical animation 
static horizontal animation (default true)
static vertical animation 
*/