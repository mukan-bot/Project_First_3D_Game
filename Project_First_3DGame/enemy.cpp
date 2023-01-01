//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "enemy.h"
#include "collision.h"

#define ENEMY_MAX	(20)

#define MODEL_PATH	("./data/MODEL/Drone/main.obj")


struct ENEMY{
	bool use;
	int objIndex;
	int colIndex;
	int hitColIndex;
	int modelIndex;
	int HP;

	XMFLOAT3 c_size;
};



ENEMY g_enemy[20];


HRESULT InitEnemy(void) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].objIndex = SetGameObject();
		SetPosition(g_enemy[i].objIndex, XMFLOAT3(0.0f, -1000.0f, 0.0f));	//Œ©‚¦‚È‚¢Š‚É¶¬‚µ‚Ä‚¨‚­

		g_enemy[i].modelIndex = SetGameModel(MODEL_PATH, g_enemy[i].objIndex, 1, CULL_MODE_NONE);

		g_enemy[i].colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);

		g_enemy[i].hitColIndex = SetCollision(LAYER_ENEMY, TYPE_BC);



		g_enemy[i].c_size = XMFLOAT3(10.0f, 10.0f, 10.0f);	//collision‚ÌƒTƒCƒY
		g_enemy[i].HP = 100;
		g_enemy[i].use = false;


		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);
		int index;
		index = GetColObjectIndex(g_enemy[i].colIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));
		index = GetColObjectIndex(g_enemy[i].hitColIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

	}

	SetEnemy(XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.01f, 0.01f, 0.01f));

	return S_OK;
}
void UninitEnemy(void) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].use = false;
		DelCollision(g_enemy[i].colIndex);
		DelCollision(g_enemy[i].hitColIndex);
		DelGameObject(g_enemy[i].objIndex);
	}
}
void UpdateEnemy(void) {

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].use) continue;

		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);

		//“–‚½‚è”»’è
		{
			int index;
			index = GetColObjectIndex(g_enemy[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, MulXMFLOAT3(scl,g_enemy[i].c_size));
			index = GetColObjectIndex(g_enemy[i].hitColIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

			if (GetColAnsUpdate(g_enemy[i].hitColIndex)) {
				g_enemy[i].HP--;
			}
			if (g_enemy[i].HP < 0) {
				SetIsClear(true);
				SetMode(MODE_RESULT);
			}
		}
	}
}
void DrawEnemy(void) {

}

void SetEnemy(XMFLOAT3 pos,XMFLOAT3 rot, XMFLOAT3 scl) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) continue;

		SetPosition(g_enemy[i].objIndex, pos);
		SetRotation(g_enemy[i].objIndex, rot);
		SetScale(g_enemy[i].objIndex, scl);
		g_enemy[i].use = true;
		break;
	}
}