#include "ClassGrafica.h"




HRESULT ClassGrafica::InitD3D(HWND hWnd)
{
    D3DPRESENT_PARAMETERS   d3dpp;
    D3DCAPS9                caps;
    D3DDEVTYPE              deviceType = D3DDEVTYPE_HAL;
    int vp = 0;
    HRESULT hr = 0;

    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

    if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
  
    d3dpp.BackBufferWidth = g_iWindowWidth;
    d3dpp.BackBufferHeight = g_iWindowHeight;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.Windowed = true;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
    d3dpp.Flags = 0;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    hr = g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        deviceType,
        hWnd,
        vp,
        &d3dpp,
        &g_pd3dDevice);



    if (FAILED(hr))
    {
        d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

        hr = g_pD3D->CreateDevice(
            D3DADAPTER_DEFAULT,
            deviceType,
            hWnd,
            vp,
            &d3dpp,
            &g_pd3dDevice);

        if (FAILED(hr))
        {
            g_pD3D->Release(); // done with d3d9 object
            ::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
            return false;
        }
    }

    g_pD3D->Release();

    return S_OK;

}

void ClassGrafica::vRender()
{
    g_pd3dDevice->Clear(0, NULL,
        D3DCLEAR_TARGET,
        D3DCOLOR_XRGB(0, 0, 255),
        1.0f, 0);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {

        if (SourceSurface != NULL)
        {
            g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
            g_pd3dDevice->UpdateSurface(SourceSurface, NULL, BackBuffer, NULL);
        }
        else
            ::MessageBox(0, L"SURFACE () - FAILED", 0, 0);
        if (BackBuffer != NULL)
            BackBuffer->Release();

        g_pd3dDevice->EndScene();
    }
    // Present the back buffer contents to the display
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT ClassGrafica::CreaSurface()
{
    HRESULT hr = E_FAIL;

    GetClientRect(hWnd, &rcWindowClient);
    g_iXOffset = (g_iWindowWidth - (rcWindowClient.right - rcWindowClient.left));
    g_iYOffset = (g_iWindowHeight - (rcWindowClient.bottom - rcWindowClient.top));

    SetWindowPos(hWnd, NULL, 0, 0,
        g_iWindowWidth + g_iXOffset,
        g_iWindowHeight + g_iYOffset,
        NULL);

    ZeroMemory(&msg, sizeof(msg));

    if (SUCCEEDED(InitD3D(hWnd))) {

        D3DXIMAGE_INFO Info;
        hr = D3DXGetImageInfoFromFile(path, &Info);


        if (hr == S_OK)
        {
            hr = g_pd3dDevice->CreateOffscreenPlainSurface(Info.Width, Info.Height,
                Info.Format,
                D3DPOOL_SYSTEMMEM,
                &SourceSurface, NULL);


            if (hr == S_OK)
            {
                hr = D3DXLoadSurfaceFromFile(SourceSurface,
                    NULL,
                    NULL,
                    path,
                    NULL, D3DX_FILTER_NONE,
                    0xFF000000, NULL);

                if (hr == S_OK)

                {
                     vRender();

                    //return S_OK;
                }
            }

        }
        else
            E_FAIL;


        MSG msg;
        msg = { };

        while (msg.message != WM_QUIT) {
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
                return E_FAIL;
        }
    }
    return S_OK;

}
