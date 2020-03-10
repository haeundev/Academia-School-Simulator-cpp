#include "stdafx.h"
#include "Title.h"
#include "GgaetIp.h"

//API : Application Programming Interface

HINSTANCE	_hInstance;
HWND		_hWnd;

POINT _ptMouse;		//마우스 용 POINT

//함수의 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;
	WNDCLASS	wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = "Game";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		"Game",
		"Game",
		WINSTYLE,
		0,
		0,
		DesignResolution.x ,
		DesignResolution.y ,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow);

	// Setup Dear ImGui context

	//메시지 루프 돌기이전에	
	SceneManager::GetInstance()->PushScene(new Title());
	SetTimer(_hWnd, 1, 1000.f / ApplicationManager::GetInstance()->GetFrameRate(), NULL);
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, iMessage, wParam, lParam))
		return true;
	return SceneManager::GetInstance()->GetNowScene()->MainProc(hWnd, iMessage, wParam, lParam);
}