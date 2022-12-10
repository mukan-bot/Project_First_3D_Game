//DLLを使う方でインクルードするやつ

#pragma once
#include <Windows.h>

//GameDLLリンク
#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/GameDLL.lib")
#else
#pragma comment (lib, "../x64/Release/GameDLL.lib")
#endif // _DEBUG

#define DLLINPORT extern "C" __declspec(dllimport) 

DLLINPORT void OutputDebug(const char* format, ...);

//XYをXYZの回転に変換して加算
DLLINPORT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);
