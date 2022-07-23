/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Drawing-App>

	This file is part of the DrawingApp project. using the Win32 API and The COM

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
#include"MainWindow.h"
#include <shobjidl.h> 


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
//{
//	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
//	if (SUCCEEDED(hr))
//	{
//		IFileOpenDialog *pFileOpen;
//
//		// Create the FileOpenDialog object.
//		hr = CoCreateInstance(
//			CLSID_FileOpenDialog, 
//			NULL,
//			CLSCTX_ALL,
//			IID_IFileOpenDialog, 
//			reinterpret_cast<void**>(&pFileOpen));
//
//		if (SUCCEEDED(hr))
//		{
//			// Show the Open dialog box.
//			hr = pFileOpen->Show(NULL);
//
//			// Get the file name from the dialog box.
//			if (SUCCEEDED(hr))
//			{
//				IShellItem *pItem;
//				hr = pFileOpen->GetResult(&pItem);
//				if (SUCCEEDED(hr))
//				{
//					PWSTR pszFilePath;
//					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//
//					// Display the file name to the user.
//					if (SUCCEEDED(hr))
//					{
//						MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
//						CoTaskMemFree(pszFilePath);
//					}
//					pItem->Release();
//				}
//			}
//			pFileOpen->Release();
//		}
//		CoUninitialize();
//	}
//	return 0;
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Drawing App", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

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
