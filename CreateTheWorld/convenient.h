//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

//よく使う計算とかを関数として持っておく

#pragma once

#include "main.h"

void OutputDebug(const char* format, ...);

//XYをXYZの回転に変換して加算
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3同士の足し算
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の引き算
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の掛け算
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3同士の割り算
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//値の最大値と最小値を指定出来る
float Clamp(float value, float min, float max);

// 内積(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// 外積(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 正規化
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3の比較
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);