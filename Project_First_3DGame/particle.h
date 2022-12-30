//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "main.h"

enum PARTICLE_TYPE {
	PLAYER_ATK1,
	PLAYER_ATK2,
	ENEMY_ATK1,
	ENEMY_ATK2,
	PARTICLE_TYPE_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

void SetColorParticle(int nIdxParticle, XMFLOAT4 col);
int SetParticle(int objIndex, PARTICLE_TYPE type, XMFLOAT4 color);