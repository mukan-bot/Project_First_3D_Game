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

// �G�l�~�[�̔z�u
void SetEnemy(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);
//���̂�ENEMY�������Ă邩
int GetAliveEnemy(void);