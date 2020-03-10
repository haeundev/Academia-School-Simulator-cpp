#include "stdafx.h"
#include "GgaetIp.h"

ApplicationManager::ApplicationManager()
{
	resolution = Vector2(1600, 900);
	DEVMODE devMode;
	int n = 0;
	while (EnumDisplaySettings(NULL, n, &devMode))
	{
		bool allowPush = true;
		Vector3 resolution;
		resolution.x = devMode.dmPelsWidth;
		resolution.y = devMode.dmPelsHeight;
		resolution.z = devMode.dmDisplayFrequency;
		for (auto r : resolutions)
		{
			if (r == resolution)
			{
				allowPush = false;
				break;
			}
		}
		if(allowPush)
			resolutions.push_back(resolution);
		n++;
	};
}

vector<Vector3> ApplicationManager::GetResolutions()
{
	return resolutions;
}

ApplicationManager* ApplicationManager::GetInstance()
{
	static ApplicationManager* instance = new ApplicationManager();
	return instance;
}

void ApplicationManager::SetFrameRate(int _frameRate)
{
	frameRate = _frameRate;
}

int ApplicationManager::GetFrameRate()
{
	return frameRate;
}

void ApplicationManager::SetResolution(int width, int height,bool _isFullScreen)
{
	resolution.x = width;
	resolution.y = height;
	if (_isFullScreen)
		EnterFullScreen();
	else if (isFullScreen)
		ExitFullScreen();
	else
		SetWindowSize();
	isFullScreen = _isFullScreen;
}

void ApplicationManager::SetResolution(int width, int height)
{
	resolution.x = width;
	resolution.y = height;
	if (isFullScreen)
	{
		ExitFullScreen();
		EnterFullScreen();
	}
}

void ApplicationManager::SetIsFullScreen(bool _isFullScreen)
{
	if (_isFullScreen)
		EnterFullScreen();
	else
		ExitFullScreen();
	isFullScreen = _isFullScreen;
}

Vector2 ApplicationManager::GetResolution()
{
	return resolution;
}

void ApplicationManager::SetDisplayFrequency(int _displayFrequency)
{
	displayFrequency = _displayFrequency;
	UpdateScreen();
}

void ApplicationManager::SetColorBit(int _colorBit)
{
	colorBit = _colorBit < 32 ? 32 : _colorBit;
	UpdateScreen();
}

void ApplicationManager::EnterFullScreen()
{
	SetWindowLongPtr(_hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
	SetWindowLongPtr(_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	DEVMODE screenSettings;

	EnumDisplaySettings(NULL, 0, &screenSettings);
	screenSettings.dmPelsWidth = resolution.x;
	screenSettings.dmPelsHeight = resolution.y;
	screenSettings.dmBitsPerPel = colorBit;
	screenSettings.dmDisplayFrequency = displayFrequency;
	screenSettings.dmFields = DM_PELSWIDTH |
		DM_PELSHEIGHT |
		DM_BITSPERPEL |
		DM_DISPLAYFREQUENCY;
	SetWindowLongPtr(_hWnd, GWL_EXSTYLE, WS_EX_LEFT);
	SetWindowLongPtr(_hWnd, GWL_STYLE, WINSTYLE);
	SetWindowPos(_hWnd, 0, 0, 0, resolution.x , resolution.y , SWP_SHOWWINDOW);
	ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN);
	ShowWindow(_hWnd, SW_MAXIMIZE);
}

void ApplicationManager::UpdateScreen()
{
	if (isFullScreen)
		EnterFullScreen();
	else
		ExitFullScreen();
}

void ApplicationManager::SetWindowSize()
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = resolution.x;
	winRect.bottom = resolution.y;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실절적으로 클라이언트 영역 크기 셋팅 함수
	SetWindowPos(_hWnd, NULL, 0, 0,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

void ApplicationManager::ExitFullScreen()
{
	SetWindowLongPtr(_hWnd, GWL_EXSTYLE, WS_EX_LEFT);
	SetWindowLongPtr(_hWnd, GWL_STYLE, WS_CAPTION);
	ChangeDisplaySettings(NULL, CDS_RESET);
	SetWindowSize();
	ShowWindow(_hWnd, SW_RESTORE);
}

bool ApplicationManager::GetIsFullScreen()
{
	return isFullScreen;
}