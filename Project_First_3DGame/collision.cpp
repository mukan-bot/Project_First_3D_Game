//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"
#include "collision.h"

#include "GameObject.h"
#include "GameModel.h"

#ifdef _DEBUG

#define CUBE_MODEL ("./data/MODEL/collision_cube.obj")

#endif // _DEBUG



COLLISION g_collision[COLLISION_MAX];



int SetCollision(COLLISION_LAYER layer,COLLISION_TYPE type) {
	int ans = -1;
	for (int i = 0; i < COLLISION_MAX;i++) {
		if (g_collision[i].use) continue;

		g_collision[i].gameObjectIndex = SetGameObject();
		g_collision[i].layer = layer;
		g_collision[i].type = type;
		g_collision[i].use = true;
#ifdef _DEBUG
		//	デバック時はcollisionの範囲を表示しておく
		g_collision[i].gameModelIndex = SetGameModel(CUBE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_NONE);
#endif // _DEBUG 

		ans = i;

		break;
	}

	return ans;
}


void DelCollision(int index) {
	g_collision[index].ans = false;
	DelGameObject(g_collision[index].gameObjectIndex);
#ifdef _DEBUG
	DelGameModel(g_collision[index].gameModelIndex);
#endif // _DEBUG

}


int GetColObjectIndex(int index) {
	return g_collision[index].gameObjectIndex;
}

bool GetColAns(int index) {
	return g_collision[index].ans;
}

bool GetColAnsUpdate(int index) {
	int i = index;

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//使われてないのも初期化したほうが条件分岐より早い気がする

	//if (!g_collision[i].use) continue;

	//BCなら半径を求める
	float r1;
	if (g_collision[i].type == TYPE_BC) {
		XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
		r1 = (size.x + size.y + size.z) / 3.0f;
	}

	for (int j = 0; j < COLLISION_MAX; j++) {
		if (!g_collision[j].use) continue;
		if (g_collision[j].layer != g_collision[i].layer) continue;	// レイヤーが違ったら比較しない
		if (g_collision[j].type != g_collision[i].type) continue;	// レイヤータイプが違ったら比較しない
		if (g_collision[i].ans && g_collision[j].ans) continue;		// 両方すでに何かに当たっている場合は比較しない
		if (i == j) continue;

		if (g_collision[j].type == TYPE_BB) {
			if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
				GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
				g_collision[i].ans = g_collision[j].ans = true;
				break;
			}
		}

		else {
			XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
			float r2 = (size.x + size.y + size.z) / 3.0f;
			if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[i].gameObjectIndex), r2)) {
				g_collision[i].ans = g_collision[j].ans = true;
				break;
			}
		}
	}


	return g_collision[i].ans;
}



void UpdateCollision(void) {

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//使われてないのも初期化したほうが条件分岐より早い気がする

	for (int i = 0; i < COLLISION_MAX; i++) {
		if (!g_collision[i].use) continue;

		//BCなら半径を求める
		float r1;
		if (g_collision[i].type == TYPE_BC) {	
			XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
			r1 = (size.x + size.y + size.z) / 3.0f;
		}

		for (int j = 0; j < COLLISION_MAX; j++) {
			if (!g_collision[j].use) continue;
			if (g_collision[j].layer != g_collision[i].layer) continue;	// レイヤーが違ったら比較しない
			if (g_collision[j].type != g_collision[i].type) continue;	// レイヤータイプが違ったら比較しない
			if (g_collision[i].ans && g_collision[j].ans) continue;		// 両方すでに何かに当たっている場合は比較しない
			if (i == j) continue;

			if (g_collision[j].type == TYPE_BB) {
				if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex),SetXMFLOAT3(0.05f)),
								GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
					g_collision[i].ans = g_collision[j].ans = true;

				}
			}

			else {
				XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
				float r2 = (size.x + size.y + size.z) / 3.0f;
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex),r1,GetPosition(g_collision[i].gameObjectIndex),r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
				}
			}
		}
	}
}

