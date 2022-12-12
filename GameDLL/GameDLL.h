//DLL���g�����ŃC���N���[�h������

#pragma once
#include <Windows.h>

//GameDLL�����N
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

//XY��XYZ�̉�]�ɕϊ����ĉ��Z
DLLINPORT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3���m�̑����Z
DLLINPORT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̈����Z
DLLINPORT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̊|���Z
DLLINPORT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̊���Z
DLLINPORT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
