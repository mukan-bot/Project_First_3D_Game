//DLL���g�����ŃC���N���[�h������
//C4190�x�����o�邯�ǁADirectX11���g�p���Ă�v���W�F�N�g�Ȃ���Ȃ��̂ŁA�X���[����悤�ɂ��Ă���

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

//�l�̍ő�l�ƍŏ��l���w��o����
DLLINPORT float Clamp(float value, float min, float max);

// ����(dot)
DLLINPORT float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// �O��(cross)
DLLINPORT void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 ���K��
DLLINPORT XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3�̔�r
DLLINPORT bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);