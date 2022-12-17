//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

//‚æ‚­Žg‚¤ŒvŽZ‚Æ‚©‚ðŠÖ”‚Æ‚µ‚ÄŽ‚Á‚Ä‚¨‚­

#pragma once

#include "main.h"

void OutputDebug(const char* format, ...);

//XY‚ðXYZ‚Ì‰ñ“]‚É•ÏŠ·‚µ‚Ä‰ÁŽZ
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3“¯Žm‚Ì‘«‚µŽZ
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯Žm‚Ìˆø‚«ŽZ
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯Žm‚ÌŠ|‚¯ŽZ
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3“¯Žm‚ÌŠ„‚èŽZ
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//’l‚ÌÅ‘å’l‚ÆÅ¬’l‚ðŽw’èo—ˆ‚é
float Clamp(float value, float min, float max);

// “àÏ(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// ŠOÏ(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 ³‹K‰»
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3‚Ì”äŠr
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);