//DLLを使う方でインクルードするやつ
//C4190警告が出るけど、DirectX11を使用してるプロジェクトなら問題ないので、スルーするようにしている

#pragma once
#include <Windows.h>

//GameDLLリンク
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

//XYをXYZの回転に変換して加算
DLLINPORT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3同士の足し算
DLLINPORT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の引き算
DLLINPORT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の掛け算
DLLINPORT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の割り算
DLLINPORT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//値の最大値と最小値を指定出来る
DLLINPORT float Clamp(float value, float min, float max);

// 内積(dot)
DLLINPORT float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// 外積(cross)
DLLINPORT void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 正規化
DLLINPORT XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3の比較
DLLINPORT bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);