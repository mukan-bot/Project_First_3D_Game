//DLL���g�����ŃC���N���[�h������

#pragma once
#include <Windows.h>

//GameDLL�����N
#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/GameDLL.lib")
#else
#pragma comment (lib, "../x64/Release/GameDLL.lib")
#endif // _DEBUG

#define DLLINPORT extern "C" __declspec(dllimport) 

DLLINPORT void OutputDebug(const char* format, ...);

//XY��XYZ�̉�]�ɕϊ����ĉ��Z
DLLINPORT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);
