//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "attack.h"
#include "collision.h"
#include "particle.h"

#define ATK_MAX	(125)

//グローバル変数
ATTACK g_atk[ATK_MAX];

//プロトタイプ宣言
void DelAtack(int index);

HRESULT InitAttack(void) {
	for (int i = 0; i < ATK_MAX; i++) {
		g_atk[i].use = false;
	}
	return S_OK;
}
void UninitAttack(void) {

}
void UpdateAttack(void) {
	for (int i = 0; i < ATK_MAX; i++) {
		if (!g_atk[i].use) continue;

		int index = g_atk[i].colObjIndex;

		// 設定フレーム数動いたら削除
		if (g_atk[i].countFlame >= g_atk[i].maxFlame) {
			DelAtack(i);
			continue;
		}

		// 当たったら削除
		if (GetColAns(g_atk[i].colIndex)) {
			DelAtack(i);
			continue;
		}


		XMFLOAT3 pos = GetPosition(index);
		XMFLOAT3 rot = GetRotation(index);

		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);

		vec.x += sinf(rot.x);
		vec.z += cosf(rot.x);
		vec.y -= tanf(rot.z);

		vec = NormalizeXMFLOAT3(vec);

		pos = AddXMFLOAT3(pos, vec);
		SetPosition(index, pos);




		
		g_atk[i].countFlame++;

	}
}
void DrawAttack(void) {

}

void SetAttack(ATK_TYPE type, int objIndex) {

	//ループの外でやったほうが早いと思う
	XMFLOAT3 pos = GetPosition(objIndex);
	XMFLOAT3 rot = GetRotation(objIndex);
	XMFLOAT3 scl = GetScale(objIndex);

	for (int i = 0; i < ATK_MAX; i++) {
		if (g_atk[i].use) continue;


		g_atk[i].countFlame = 0;


		int index = -1;
		switch (type)
		{
		case ATK_PLAYER_1:
			g_atk[i].maxFlame = 60;

			g_atk[i].colIndex = SetCollision(LAYER_PLAYER_ATK, TYPE_BC);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.01f, 0.01f, 0.01f));
			
			SetParticle(g_atk[i].colObjIndex, PLAYER_ATK1, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case ATK_PLAYER_2:
			g_atk[i].maxFlame = 5;
			g_atk[i].colIndex = SetCollision(LAYER_PLAYER_ATK, TYPE_BC);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.1f, 0.1f, 0.1f));
			break;

		case ATK_ENEMY_1:
			g_atk[i].maxFlame = 120;
			g_atk[i].colIndex = SetCollision(LAYER_ENEMY_ATK, TYPE_BB);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(1.0f, 1.0f, 1.0f));
			break;

		case ATK_ENEMY_2:
			g_atk[i].maxFlame = 120;
			g_atk[i].colIndex = SetCollision(LAYER_ENEMY_ATK, TYPE_BB);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(1.0f, 1.0f, 1.0f));
			break;
		}

		if (g_atk[i].colIndex == -1 || index == -1) {
			break;
		}



		g_atk[i].use = true;

		break;
	}
}

void DelAtack(int index) {
	DelCollision(g_atk[index].colIndex);
	g_atk[index].use = false;
}

