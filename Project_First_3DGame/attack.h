//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "main.h"

enum ATK_TYPE {	//MEMO:今回は攻撃は四種類固定
	ATK_PLAYER_1 = 0,
	ATK_PLAYER_2,
	ATK_ENEMY_1,
	ATK_ENEMY_2,

	ATK_TYPE_MAX,
};


struct ATTACK{
	bool use;				// 使われているか
	ATK_TYPE type;			// どの攻撃か
	int colIndex;			// 当たり判定
	int colObjIndex;		// 当たり判定のオブジェクトインデックス
	int fieldColIndex;		// フィールドとの当たり判定
	int fieldColObjIndex;	// フィールドとの当たり判定のオブジェクトインデックス
	int modelIndex;			// モデルを表示する時用のgameModelインデックス

	int maxFlame;			// 何フレーム残るか
	int countFlame;			// 今何フレーム経ったか

	XMFLOAT3 vec;			//移動の向き（正規化されてなくてもいい）
};


HRESULT InitAttack(void);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);
// 攻撃をセット
void SetAttack(ATK_TYPE type, int objIndex);
