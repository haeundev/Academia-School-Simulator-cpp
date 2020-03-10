#include "stdafx.h"
#include "GgaetIp.h"
#include "Direct3D.h"
#pragma warning (disable:4996)

Direct2D* Direct2D::GetInstance()
{
	static Direct2D* instance = new Direct2D();
	return instance;
}

Direct2D::Direct2D()
{
	HWND hWnd = GetActiveWindow();
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	RECT rt;
	GetClientRect(hWnd, &rt);
	D2D1_SIZE_U size = { rt.right - rt.left,rt.bottom - rt.top };

	FLOAT dpiX;
	FLOAT dpiY;
	factory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX,
			dpiY
		);

	
	IDXGISurface1* pBackBuffer;
	Direct3D::GetInstance()->GetSwapChain()->GetBuffer(0,
		__uuidof(IDXGISurface1),
		(void**)&pBackBuffer);
	factory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props,&renderTarget);
	//factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);

	factory->Release();

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));

	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory));
}
//
//ID2D1HwndRenderTarget* Direct2D::GetRenderTarget()
//{
//	return renderTarget;
//}

ID2D1RenderTarget* Direct2D::GetRenderTarget()
{
	return renderTarget;
}

ID2D1Bitmap* Direct2D::CreateBitmap(wstring path, D2D1_RECT_F* size)
{
	IWICBitmapDecoder* decoder;
	IWICFormatConverter* converter;

	UINT width, height;
	imageFactory->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
	imageFactory->CreateFormatConverter(&converter);
	IWICBitmapFrameDecode* frame;
	decoder->GetFrame(0, &frame);
	frame->GetSize(&width, &height);
	size->right = width;
	size->bottom = height;
	converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	ID2D1Bitmap* bitmap;
	renderTarget->CreateBitmapFromWicBitmap(converter, NULL, &bitmap);
	converter->Release();
	decoder->Release();
	frame->Release();
	return bitmap;
}

IDWriteTextLayout* Direct2D::CreateTextLayout(wstring str,wstring fontName,wstring locale,float fontSize,int maxWidth,int maxHeight)
{
	IDWriteTextFormat* textFormat;
	writeFactory->CreateTextFormat(fontName.c_str(), NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, locale.c_str(), &textFormat);

	IDWriteTextLayout* layout;
	writeFactory->CreateTextLayout(str.c_str(), str.length(), textFormat, maxWidth, maxHeight, &layout);
	return layout;
}