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

// エネミーの配置
void SetEnemy(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);
//何体のENEMYが生きてるか
int GetAliveEnemy(void);