#pragma once
#include"ClassGrafica.h"
#include<Windows.h>
#include <commdlg.h>
#include<string.h>
#include <string>
#define _CRTDBG_MAP_ALLOC // For detecting memory leaks
#include <stdlib.h> // For detecting memory leaks
#include <crtdbg.h> // For detecting memory leaks


#define SAFE_DELETE(ptr) { if (ptr) { delete (ptr); (ptr)=NULL; } }
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }





WNDCLASSEX   wcx;


LRESULT WINAPI fnMessageProcessor(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK fnMessageProcessor(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

    case WM_CLOSE:
        if (MessageBox(hWnd, L"chiudi finestra?", L"mia applicazione", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hWnd);
        }




        return 0;

    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
