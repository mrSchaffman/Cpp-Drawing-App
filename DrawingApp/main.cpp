/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Drawing-App>

	This file is part of the DrawingApp project. using the Win32 API

	DrawingApp is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	DrawingApp is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include<Windows.h>

// some data for my window
struct SomeData {
	int a;
	int b;
};
inline SomeData* GetAppState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	SomeData *pState = reinterpret_cast<SomeData*>(ptr);
	return pState;
}

// The Callback Signature, The Procedure for This "hello World" Window.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	// Retrieve the Data associated whith the hwnd
	SomeData *pState;
	if (uMessage == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<SomeData*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		pState = GetAppState(hwnd);
	}

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);				
										
										
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT paintStructure;		

		// paint the Window
		BeginPaint(hwnd, &paintStructure);	


		FillRect(paintStructure.hdc, &paintStructure.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); 
		EndPaint(hwnd, &paintStructure);
	}
	return 0;
	//case WM_SIZE:
	//{
	//	int width = LOWORD(lParam);  // Macro to get the low-order word.
	//	int height = HIWORD(lParam); // Macro to get the high-order word.

	//	// Respond to the message:
	//	OnSize(hwnd, (UINT)wParam, width, height);
	//}
	//break;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL | MB_ICONWARNING) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	}

	// use message default handler behavior for other messages
	return DefWindowProc(hwnd, uMessage, wParam, lParam);
}
void OnSize(HWND hwnd, UINT flag, int width, int height)
{
	// Handle resizing
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPInstance, PWSTR pCmdLine, int nCmdShow)
{
	// initialize the Data
	SomeData *pState = new SomeData;

	if (pState == NULL)
	{
		return 0;
	}

	// Create, set a Window Class associate with my Window and register it with the opereratin System

	WNDCLASS winClass = {};		// Commond data related to a window
	const wchar_t theClassName[] = L"Hello World Window Class";

	winClass.lpfnWndProc = WindowProc;		
	winClass.hInstance = hInstance;			
	winClass.lpszClassName = theClassName;	

	RegisterClass(&winClass);

	// Create the Window
	// this function return a "handle" to the Created window, used as target to messages coming from the operating system
	HWND hwnd = CreateWindowEx(
		0,						
		theClassName,			
		L"Hello World",			
		WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		CW_USEDEFAULT,	
		NULL,			
		NULL,			
		hInstance,
		pState
	);

	// chech if the Window was create succefully
	if (hwnd == NULL)
		return 0;
	// show the Window.
	ShowWindow(hwnd, nCmdShow);

	// enter the message loop: The application needs a loop to retrieve the messages and dispatch them to the correct windows.
	MSG message = {};
	while (GetMessage(&message, NULL, 0, 0) > 0)		
	{											
		// exemple of message: #define WM_LBUTTONDOWN    0x0201

		TranslateMessage(&message);				
		DispatchMessage(&message);				
	}


	return 0;
}
