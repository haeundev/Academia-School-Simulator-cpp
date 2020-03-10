#pragma once
#include <d3d11_1.h>
#include <d3d11.h>
#pragma comment (lib,"d3d11.lib")

class Direct3D
{
private:
	Direct3D();
	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
public:
	static Direct3D* GetInstance();
	ID3D11Device* GetDevice() { return g_pd3dDevice; }
	IDXGISwapChain* GetSwapChain() { return g_pSwapChain; }
	ID3D11RenderTargetView* GetRenderTargetView() { return 	g_mainRenderTargetView; }
	ID3D11DeviceContext* GetDeviceContext() { return g_pd3dDeviceContext; }
};

