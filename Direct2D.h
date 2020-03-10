#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>

#pragma comment (lib,"windowscodecs.lib")
#pragma comment(lib,"d2d1.lib")

using namespace std;

class Direct2D
{
private:
	ID2D1Factory1* factory;
	IDWriteFactory* writeFactory;
	//ID2D1HwndRenderTarget* renderTarget;
	ID2D1RenderTarget* renderTarget;
	IWICImagingFactory* imageFactory;



	Direct2D();
public:
	static Direct2D* GetInstance();

	//ID2D1HwndRenderTarget* GetRenderTarget();
	ID2D1RenderTarget* GetRenderTarget();
	ID2D1Bitmap* CreateBitmap(wstring path, D2D1_RECT_F* size);
	IDWriteTextLayout* CreateTextLayout(wstring str, wstring fontName, wstring locale, float fontSize, int maxWidth, int maxHeight);
};

