Problem Statement:
1.	Create an project icon. 
2.	In center of window, yellow color of wireframe rectangle. 
3.	Base code should be 03-Icon
4.	Windows should be maximized by default
4.	Window background and rectangle inside color should be black. 
5.	Refer MiniProject code where Ellipse() is used. Instead of Ellipse(), use Rectangle()
6.	Use RECT structure to pass parameters to Rectangle()
7.	Use Pen-CreatePen() instead of CreateSolidBrush(). 
8.	Pen thickness should be 5. 
9.	Yellow rectangle must be in center even on window resize. 
10.	WM_PAINT and WM_SIZE needs to be handled. 
11.	Length of rectangle should be 400. 
12.	Height of rectangle should be 400. 
13.	Define Macros - DEFAULT_RECT_WIDTH & DEFAULT_RECT_HEIGHT as 400. 
14.	POINT structure should be used for all types of x and y co-ordinates. 
15.	In WM_SIZE, fetch latest updated width using LOWORD(lParam) and latest updated height using HIWORD(lParam)
17.	Use RECT as static. Use rectangle width and height as static. 
18.	rectangle.left = windowCenter.x - (rectWidth / 2)
============================================================
19.	Handle WM_CHAR
20.	On T press, rectangle.top should go above by 20 pixels. 
21.	On t press, rectangle.top should go below by 20 pixels. 
22.	On B press, rectangle.bottom should go below by 20 pixels. 
23.	On b press, rectangle.bottom should go above by 20 pixels. 
24.	On L press, rectangle.left should go left by 20 pixels. 
25. On l press, rectangle.left should go right by 20 pixels. 
26. On R press, rectangle.right should go right by 20 pixels. 
27. On r press, rectangle.right should go left by 20 pixels. 
28.	After above key presses, calculate updated rectangle height and width in WM_PAINT
29.	Exit on escape key. 
30. Rectangle should be reset on space bar. 