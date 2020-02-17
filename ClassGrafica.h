#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class ClassGrafica
{

public:
	LPDIRECT3D9             g_pD3D = NULL;
	LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
	LPDIRECT3DSURFACE9      BackBuffer = NULL;
	LPDIRECT3DSURFACE9      SourceSurface = NULL;

	int g_iXOffset = 0;
	int g_iYOffset = 0;
	

	
	LPCWSTR path = L"c:/Users/Angyreal/pictures/image.jpg";
	//LPCWSTR path = L"c:/th.jpg";


	MSG          msg;
	RECT         rcWindowClient;
	HWND         hWnd;
	int g_iWindowWidth = 800;
	int g_iWindowHeight = 600;

	HRESULT InitD3D(HWND hWnd);
	void vRender();
	HRESULT CreaSurface();

};

