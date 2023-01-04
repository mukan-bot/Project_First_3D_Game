//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "main.h"

enum ATK_TYPE {	//MEMO:ç°âÒÇÕçUåÇÇÕéléÌóﬁå≈íË
	ATK_PLAYER_1 = 0,
	ATK_PLAYER_2,
	ATK_ENEMY_1,
	ATK_ENEMY_2,

	ATK_TYPE_MAX,
};


struct ATTACK{
	bool use;

	int colIndex;
	int colObjIndex;
	int fieldColIndex;
	int fieldColObjIndex;
	int modelIndex;

	int maxFlame;
	int countFlame;
};


HRESULT InitAttack(void);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);

void SetAttack(ATK_TYPE type, int objIndex);
