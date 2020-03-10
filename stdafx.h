#pragma once

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>
#include "Vector2.h"

using namespace std;

#define DesignResolution Vector2(1600,900) 
#define WINSTYLE WS_VISIBLE || WS_BORDER || WS_CAPTION

#define GRID_STARTPOINT Vector2(-DesignResolution.x / 2, DesignResolution.y)

#define TotalGridX 50
#define TotalGridY 50
#define GridWidth 128
#define GridHeight 128

#define CameraMoveSpeed 30
#define CharacterMoveSpeed 9

#define ToWorkPosition Vector2(5468, -4728)
#define ToSchoolPosition Vector2(5468, -4728)

#define PI 3.14

enum class MTYPE
{
	TIME,
	HIRED,
	FIRED,
	SCHEDULE_UP,
	SCHEDULE_DOWN,
	WORK,
	BUDGET_PLUS,
	BUDGET_MINUS,
	STAR
};

enum class ZORDER
{
	LAND,
	FLOOR,
	ZONE,
	ZONE_TEXT,
	WALL,
	OBJECT,
	GUIDELINE,
	FOLLOW_MOUSE_SPRITE,
	TILE_POLY_DRAW,
	CHARACTER,
	UI_WINDOW = 100,
	UI_BUTTONS_ON_WINDOW,
	UI_TEXTS_ON_WINDOW,
	POLY_ON_UI,
	SCREEN
};

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

#include "GgaetIp.h"