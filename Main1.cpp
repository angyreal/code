

#include"Main1.h"

ClassGrafica InitGraf;

using namespace std;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int iCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
   
    const wchar_t CLASS_NAME[] = L"mio nome class";
    
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = fnMessageProcessor;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = NULL;
    wcx.lpszClassName = CLASS_NAME;
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx (&wcx);
    
    InitGraf.hWnd = CreateWindowEx(
        0, 
        CLASS_NAME,
        L"Title Demo",
        WS_OVERLAPPEDWINDOW,
        //CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0, InitGraf.g_iWindowWidth, InitGraf.g_iWindowHeight,
        NULL, 
        NULL, 
        hInstance, 
        NULL
    );

    if (InitGraf.hWnd == NULL)
    {
        return 0;
    }

    
    ShowWindow(InitGraf.hWnd, iCmdShow);
    
    
    InitGraf.CreaSurface();
    
    InitGraf.msg = { };
    while (GetMessage(&InitGraf.msg, NULL, 0, 0))
    {
        TranslateMessage(&InitGraf.msg);
        DispatchMessage(&InitGraf.msg);
    }
    
    return 0;

}

