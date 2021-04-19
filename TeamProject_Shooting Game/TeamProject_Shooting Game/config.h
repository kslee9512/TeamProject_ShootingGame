// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "TargetManager.h"

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, * PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;