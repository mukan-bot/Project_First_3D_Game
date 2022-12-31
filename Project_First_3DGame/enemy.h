//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once


HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);