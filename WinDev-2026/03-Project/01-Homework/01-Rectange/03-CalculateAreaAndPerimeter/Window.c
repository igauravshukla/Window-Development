// Header Files
#include<windows.h>		// This is the most important header file of Win32 SDK

// including our own header file
#include "Window.h"

// Defining rectangle width as constant
#define DEFAULT_RECT_WIDTH		400
#define DEFAULT_RECT_HEIGHT		400

// Define constant colors
#define BACKGROUND_BLACK_COLOR	RGB(0, 0, 0)
#define RECTANGLE_YELLOW_COLOR	RGB(255, 244, 79)

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
		TEXT("Gaurav WindDev-2026 Project"),		// window caption bar text
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

	// RECT structure for window (which is rectangle in shape) 
	static RECT WindowRect;

	// handle to device context (painter)
	static HDC hdc = NULL;

	// structure to paint
	PAINTSTRUCT ps;

	HBRUSH hBrush_Background = NULL;
	HPEN hPen_Rectangle = NULL;

	// members to hold the window width and height
	static unsigned int windowWidth = 0;
	static unsigned int windowHeight = 0;

	// members to hold the updated rectangle width and height
	static unsigned int rectangleWidth = DEFAULT_RECT_WIDTH;
	static unsigned int rectangleHeight = DEFAULT_RECT_HEIGHT;

	unsigned int rectangleArea = 0;
	unsigned int rectanglePerimeter = 0;

	// Point structure used to have x and y co-ordinate of window center
	static POINT windowCenter;

	// RECT structure having co-ordinates for rendering the rectangle
	static RECT rectangle;

	// Display Message Strings
	TCHAR strRectAreaDisplayMessage[255];
	TCHAR strRectPerimeterDisplayMessage[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		// get the painter to paint for your window
		hdc = BeginPaint(hwnd, &ps);

		// color the client area background with black color
		hBrush_Background = CreateSolidBrush(BACKGROUND_BLACK_COLOR);

		// Give this newly created background brush to the painter hdc (select this new brush)
		SelectObject(hdc, hBrush_Background);

		// Now, fill the client area rectangle with the selected brush color
		FillRect(hdc, &WindowRect, hBrush_Background);

		// Draw yellow wireframe rectangle
		hPen_Rectangle = CreatePen(PS_SOLID, 5, RECTANGLE_YELLOW_COLOR);

		// Give this newly created rectangle brush to the painter hdc (select this new brush)
		SelectObject(hdc, hPen_Rectangle);

		// Render Rectangle on UI
		Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

		// Recalculate the updated rectangle height and width
		rectangleWidth = rectangle.right - rectangle.left;
		rectangleHeight = rectangle.bottom - rectangle.top;

		// Now delete the brush for rectangle
		if (hPen_Rectangle)
		{
			DeleteObject(hPen_Rectangle);
			hPen_Rectangle = NULL;
		}

		// Now delete the bursh for background
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
		// zero out the RECT structure
		ZeroMemory((void*)&WindowRect, sizeof(RECT));

		// get the client area rectangle of your window
		GetClientRect(hwnd, &WindowRect);

		windowWidth = LOWORD(lParam);
		windowHeight = HIWORD(lParam);

		// set the center of window as center of rectangle
		windowCenter.x = windowWidth / 2;
		windowCenter.y = windowHeight / 2;

		ZeroMemory((void*)&rectangle, sizeof(RECT));
		rectangle.left = windowCenter.x - (rectangleWidth / 2);
		rectangle.top = windowCenter.y - (rectangleHeight / 2);
		rectangle.right = windowCenter.x + (rectangleWidth / 2);
		rectangle.bottom = windowCenter.y + (rectangleHeight / 2);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// Exit the application on escape key press
			DestroyWindow(hwnd);
			break;
		case VK_SPACE:
			// Reset the rectangle position by bringing it on center with default height and width
			rectangleWidth = DEFAULT_RECT_WIDTH;
			rectangleHeight = DEFAULT_RECT_HEIGHT;

			ZeroMemory((void*)&rectangle, sizeof(RECT));
			rectangle.left = windowCenter.x - (rectangleWidth / 2);
			rectangle.top = windowCenter.y - (rectangleHeight / 2);
			rectangle.right = windowCenter.x + (rectangleWidth / 2);
			rectangle.bottom = windowCenter.y + (rectangleHeight / 2);

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 'T':
			// On T key press, the top edge of rectangle should go above by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top - 20;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 't':
			// On t key press, the top edge of rectangle should go below by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top + 20;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'B':
			// On B key press, the bottom edge of rectangle should go below by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom + 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'b':
			// On b key press, the bottom edge of rectangle should go above by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom - 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'L':
			// On L key press, the left edge of rectangle should go left by 20 pixels
			rectangle.left = rectangle.left - 20;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'l':
			// On l key press, the left edge of rectangle should go right by 20 pixels
			rectangle.left = rectangle.left + 20;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'R':
			// On R key press, the right edge of rectangle should go right by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right + 20;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'r':
			// On r key press, the right edge of rectangle should go left by 20 pixels
			rectangle.left = rectangle.left;
			rectangle.top = rectangle.top;
			rectangle.right = rectangle.right - 20;
			rectangle.bottom = rectangle.bottom;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'A':
		case 'a':
			// On A/a key press, the area of the rectangle to be displayed
			rectangleArea = rectangleWidth * rectangleHeight;

			wsprintf(	strRectAreaDisplayMessage,
						TEXT("Current Rectange Width = %u pixels\nCurrent Rectange Height = %u pixels\nCurrent Rectange Area = %u square pixels"), 
						rectangleWidth, rectangleHeight, rectangleArea);

			MessageBox(	hwnd,
						strRectAreaDisplayMessage,
						TEXT("Area of Rectangle"),
						MB_OK);
			break;
		case 'P':
		case 'p':
			// On P/p key press, the perimeter of the rectangle to be displayed
			rectanglePerimeter = 2 * (rectangleWidth + rectangleHeight);

			wsprintf(	strRectPerimeterDisplayMessage,
						TEXT("Current Rectange Width = %u pixels\nCurrent Rectange Height = %u pixels\nCurrent Rectange Perimeter = %u square pixels"),
						rectangleWidth, rectangleHeight, rectanglePerimeter);

			MessageBox(	hwnd,
						strRectPerimeterDisplayMessage,
						TEXT("Perimeter of Rectangle"),
						MB_OK);
			break;
		default:
			break;
		}
		break;

	case WM_DESTROY:
		// Exit the application
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	// Forward the message to Default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
