//DLL‚ğg‚¤•û‚ÅƒCƒ“ƒNƒ‹[ƒh‚·‚é‚â‚Â

#pragma once
#include <Windows.h>

//GameDLLƒŠƒ“ƒN
//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/GameDLL.lib")
#else
#pragma comment (lib, "../x64/Release/GameDLL.lib")
#endif // _DEBUG

#define DLLINPORT extern "C" __declspec(dllimport) 

DLLINPORT void OutputDebug(const char* format, ...);

//XY‚ğXYZ‚Ì‰ñ“]‚É•ÏŠ·‚µ‚Ä‰ÁZ
DLLINPORT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3“¯m‚Ì‘«‚µZ
DLLINPORT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯m‚Ìˆø‚«Z
DLLINPORT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯m‚ÌŠ|‚¯Z
DLLINPORT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯m‚ÌŠ„‚èZ
DLLINPORT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
