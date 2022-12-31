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
		//	ƒfƒoƒbƒNŽž‚Ícollision‚Ì”ÍˆÍ‚ð•\Ž¦‚µ‚Ä‚¨‚­
		g_collision[i].gameModelIndex = SetGameModel(CUBE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_NONE);
#endif // _DEBUG 

		ans = i;

		break;
	}

#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetCollision‚Å-1‚ª•Ô‚³‚ê‚Ü‚µ‚½");
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

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//Žg‚í‚ê‚Ä‚È‚¢‚Ì‚à‰Šú‰»‚µ‚½‚Ù‚¤‚ªðŒ•ªŠò‚æ‚è‘‚¢‹C‚ª‚·‚é

	//BC‚È‚ç”¼Œa‚ð‹‚ß‚é
	float r1 = 0;
	if (g_collision[i].type == TYPE_BC) {
		XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
		r1 = (size.x + size.y + size.z) / 3.0f;
		r1 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
	}

	for (int j = 0; j < COLLISION_MAX; j++) {
		if (!g_collision[j].use) continue;
		if (g_collision[i].ans && g_collision[j].ans) continue;		// —¼•û‚·‚Å‚É‰½‚©‚É“–‚½‚Á‚Ä‚¢‚éê‡‚Í”äŠr‚µ‚È‚¢


		//UŒ‚Œn‚ÌƒŒƒCƒ„[‚Ìê‡‚Ì”»’è
		if (g_collision[i].layer == LAYER_PLAYER_ATK && g_collision[j].layer == LAYER_ENEMY ||
			g_collision[j].layer == LAYER_PLAYER_ATK && g_collision[i].layer == LAYER_ENEMY) {

			if (g_collision[j].type == TYPE_BB) {
				if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
					GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
					g_collision[i].ans = g_collision[j].ans = true;
					continue;
				}
			}

			else {
				XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
				float r2 = (size.x + size.y + size.z) / 3.0f;
				r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
					continue;
				}
			}
		}

		if (g_collision[i].layer == LAYER_ENEMY_ATK && g_collision[j].layer == LAYER_PLAYER ||
			g_collision[j].layer == LAYER_ENEMY_ATK && g_collision[i].layer == LAYER_PLAYER) {

			if (g_collision[j].type == TYPE_BB) {
				if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
					GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
					g_collision[i].ans = g_collision[j].ans = true;
					continue;
				}
			}

			else {
				XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
				float r2 = (size.x + size.y + size.z) / 3.0f;
				r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
					continue;
				}
			}
		}

		//ATKŒn‚Ìcollision“¯Žm‚Í“–‚½‚Á‚Ä‚¢‚Ä‚à–³Ž‹‚·‚éi˜AŽË‚·‚é‚ÆŠî–{d‚È‚é‚©‚çj
		if (g_collision[i].layer == LAYER_ENEMY_ATK)continue;
		if (g_collision[i].layer == LAYER_PLAYER_ATK)continue;

		if (g_collision[j].layer != g_collision[i].layer) continue;	// ƒŒƒCƒ„[‚ªˆá‚Á‚½‚ç”äŠr‚µ‚È‚¢
		if (g_collision[j].type != g_collision[i].type) continue;	// ƒŒƒCƒ„[ƒ^ƒCƒv‚ªˆá‚Á‚½‚ç”äŠr‚µ‚È‚¢
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
			r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
			if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[i].gameObjectIndex), r2)) {
				g_collision[i].ans = g_collision[j].ans = true;
				break;
			}
		}
	}


	return g_collision[i].ans;
}



void UpdateCollision(void) {

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//Žg‚í‚ê‚Ä‚È‚¢‚Ì‚à‰Šú‰»‚µ‚½‚Ù‚¤‚ªðŒ•ªŠò‚æ‚è‘‚¢‹C‚ª‚·‚é

	for (int i = 0; i < COLLISION_MAX; i++) {
		if (!g_collision[i].use) continue;

		//BC‚È‚ç”¼Œa‚ð‹‚ß‚é
		float r1;
		if (g_collision[i].type == TYPE_BC) {	
			XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
			r1 = (size.x + size.y + size.z) / 3.0f;
			r1 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
		}

		for (int j = 0; j < COLLISION_MAX; j++) {
			if (!g_collision[j].use) continue;
			if (g_collision[i].ans && g_collision[j].ans) continue;		// —¼•û‚·‚Å‚É‰½‚©‚É“–‚½‚Á‚Ä‚¢‚éê‡‚Í”äŠr‚µ‚È‚¢

			//UŒ‚Œn‚ÌƒŒƒCƒ„[‚Ìê‡‚Ì”»’è
			if (g_collision[i].layer == LAYER_PLAYER_ATK && g_collision[j].layer == LAYER_ENEMY || 
				g_collision[j].layer == LAYER_PLAYER_ATK && g_collision[i].layer == LAYER_ENEMY) {

				if (g_collision[j].type == TYPE_BB) {
					if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
						GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
				else {
					XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
					float r2 = (size.x + size.y + size.z) / 3.0f;
					r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
			}
			if (g_collision[i].layer == LAYER_ENEMY_ATK && g_collision[j].layer == LAYER_PLAYER ||
				g_collision[j].layer == LAYER_ENEMY_ATK && g_collision[i].layer == LAYER_PLAYER) {

				if (g_collision[j].type == TYPE_BB) {
					if (CollisionBB(GetPosition(g_collision[i].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[i].gameObjectIndex), SetXMFLOAT3(0.05f)),
						GetPosition(g_collision[j].gameObjectIndex), DivXMFLOAT3(GetScale(g_collision[j].gameObjectIndex), SetXMFLOAT3(0.05f)))) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}

				else {
					XMFLOAT3 size = GetScale(g_collision[j].gameObjectIndex);
					float r2 = (size.x + size.y + size.z) / 3.0f;
					r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}

			}

			//ATKŒn‚Ìcollision“¯Žm‚Í“–‚½‚Á‚Ä‚¢‚Ä‚à–³Ž‹‚·‚éi˜AŽË‚·‚é‚ÆŠî–{d‚È‚é‚©‚çj
			if (g_collision[i].layer == LAYER_ENEMY_ATK)continue;
			if (g_collision[i].layer == LAYER_PLAYER_ATK)continue;

			//‚»‚Ì‘¼‚Ì“–‚½‚è”»’è‚Ì”»’è
			if (g_collision[j].layer != g_collision[i].layer) continue;	// ƒŒƒCƒ„[‚ªˆá‚Á‚½‚ç”äŠr‚µ‚È‚¢
			if (g_collision[j].type != g_collision[i].type) continue;	// ƒ^ƒCƒv‚ªˆá‚Á‚½‚ç”äŠr‚µ‚È‚¢
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
				r2 *= 10;	//Œ©‚½–Ú‚Æ”ÍˆÍ‚ð‚ ‚í‚¹‚éˆ×
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex),r1,GetPosition(g_collision[i].gameObjectIndex),r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
				}
			}
		}
	}
}

