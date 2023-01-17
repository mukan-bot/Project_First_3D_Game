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

#define CUBE_MODEL ("data/MODEL/collision_cube.obj")
#define SPHERE_MODEL ("data/MODEL/collision_sphere.obj")

#endif // _DEBUG



COLLISION g_collision[COLLISION_MAX];



int SetCollision(COLLISION_LAYER layer,COLLISION_TYPE type) {
	int ans = -1;
	for (int i = 0; i < COLLISION_MAX; i++) {
		if (g_collision[i].use) continue;

		g_collision[i].gameObjectIndex = SetGameObject();
		g_collision[i].layer = layer;
		g_collision[i].type = type;
		g_collision[i].use = true;

#ifdef _DEBUG
		//	デバック時はcollisionの範囲を表示しておくワイヤーフレームで表示しておく
		if (type == TYPE_BB) {
			g_collision[i].gameModelIndex = SetGameModel(CUBE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_BACK);
			SetGameModeFill(g_collision[i].gameModelIndex,D3D11_FILL_WIREFRAME);
		}
		else if (type == TYPE_BC) {
			g_collision[i].gameModelIndex = SetGameModel(SPHERE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_BACK);
			SetGameModeFill(g_collision[i].gameModelIndex, D3D11_FILL_WIREFRAME);
	}
#endif // _DEBUG 

		ans = i;
		break;
	}

#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetCollisionで-1が返されました\n");
	}
#endif // _DEBUG


	return ans;
}


void DelCollision(int index) {
	g_collision[index].ans = false;
	DelGameObject(g_collision[index].gameObjectIndex);
	g_collision[index].use = false;

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
	if (!g_collision[i].use) {
		g_collision[i].ans = false;
		return false;	//使われてないから終了
	}
	UpdateCollision();
	return g_collision[i].ans;
}


void InitCollision(void) {
	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].use = false;	
}


void UpdateCollision(void) {

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//使われてないのも初期化したほうが条件分岐より早い気がする

	for (int i = 0; i < COLLISION_MAX; i++) {
		if (!g_collision[i].use) continue;

		//BCなら半径を求める
		float r1 = 0.0f;
		if (g_collision[i].type == TYPE_BC) {	
			XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
			r1 = (size.x + size.y + size.z) / 3.0f;
			r1 *= 10;	//見た目と範囲をあわせる為
		}

		for (int j = 0; j < COLLISION_MAX; j++) {
			if (!g_collision[j].use) continue;
			if (g_collision[i].ans && g_collision[j].ans) continue;		// 両方すでに何かに当たっている場合は比較しない

			//攻撃系のレイヤーの場合の判定(PLAYERの攻撃)
			if (g_collision[i].layer == LAYER_PLAYER_ATK && g_collision[j].layer == LAYER_ENEMY || 
				g_collision[j].layer == LAYER_PLAYER_ATK && g_collision[i].layer == LAYER_ENEMY) {
				// BB
				if (g_collision[j].type == TYPE_BB) {
					if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
						GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
				// BC
				else {
					XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
					float r2 = (size.x + size.y + size.z) / 3.0f;
					r2 *= 10;	//見た目と範囲をあわせる為
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
			}
			//攻撃系のレイヤーの場合の判定(ENEMYの攻撃)
			if (g_collision[i].layer == LAYER_ENEMY_ATK && g_collision[j].layer == LAYER_PLAYER ||
				g_collision[j].layer == LAYER_ENEMY_ATK && g_collision[i].layer == LAYER_PLAYER) {
				// BB
				if (g_collision[j].type == TYPE_BB) {
					if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
						GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
				// BC
				else {
					XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
					float r2 = (size.x + size.y + size.z) / 3.0f;
					r2 *= 10;	//見た目と範囲をあわせる為
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}

			}

			//ATK系のcollision同士は当たっていても無視する（連射すると基本重なるから）
			if (g_collision[i].layer == LAYER_ENEMY_ATK)continue;
			if (g_collision[i].layer == LAYER_PLAYER_ATK)continue;
			//HIT判定用のcollisionは攻撃との判定に使うから攻撃以外は無視
			if (g_collision[i].layer == LAYER_ENEMY) continue;
			if (g_collision[i].layer == LAYER_PLAYER) continue;

			//その他の当たり判定の判定
			if (g_collision[j].layer != g_collision[i].layer) continue;	// レイヤーが違ったら比較しない
			if (g_collision[j].type != g_collision[i].type) continue;	// タイプが違ったら比較しない
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
				r2 *= 10;	//見た目と範囲をあわせる為
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex),r1,GetPosition(g_collision[i].gameObjectIndex),r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
				}
			}
		}
	}
}

