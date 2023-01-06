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
	for (int i = 0; i < COLLISION_MAX;i++) {
		if (g_collision[i].use) continue;

		g_collision[i].gameObjectIndex = SetGameObject();
		g_collision[i].layer = layer;
		g_collision[i].type = type;
		g_collision[i].use = true;
#ifdef _DEBUG
		//	�f�o�b�N����collision�͈̔͂�\�����Ă����i�d�������U�����Ă����j
		//if (type == TYPE_BB)g_collision[i].gameModelIndex = SetGameModel(CUBE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_BACK);
		//else if (type == TYPE_BC)g_collision[i].gameModelIndex = SetGameModel(SPHERE_MODEL, g_collision[i].gameObjectIndex, 0, CULL_MODE_NONE);
#endif // _DEBUG 

		ans = i;

		break;
	}

#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetCollision��-1���Ԃ���܂���\n");
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
		return false;	//�g���ĂȂ�����I��
	}
	UpdateCollision();
	return g_collision[i].ans;
}


void InitCollision(void) {
	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].use = false;	

}


void UpdateCollision(void) {

	for (int i = 0; i < COLLISION_MAX; i++) g_collision[i].ans = false;	//�g���ĂȂ��̂������������ق������������葁���C������

	for (int i = 0; i < COLLISION_MAX; i++) {
		if (!g_collision[i].use) continue;

		//BC�Ȃ甼�a�����߂�
		float r1;
		if (g_collision[i].type == TYPE_BC) {	
			XMFLOAT3 size = GetScale(g_collision[i].gameObjectIndex);
			r1 = (size.x + size.y + size.z) / 3.0f;
			r1 *= 10;	//�����ڂƔ͈͂����킹���
		}

		for (int j = 0; j < COLLISION_MAX; j++) {
			if (!g_collision[j].use) continue;
			if (g_collision[i].ans && g_collision[j].ans) continue;		// �������łɉ����ɓ������Ă���ꍇ�͔�r���Ȃ�

			//�U���n�̃��C���[�̏ꍇ�̔���(PLAYER�̍U��)
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
					r2 *= 10;	//�����ڂƔ͈͂����킹���
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}
			}
			//�U���n�̃��C���[�̏ꍇ�̔���(ENEMY�̍U��)
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
					r2 *= 10;	//�����ڂƔ͈͂����킹���
					if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex), r1, GetPosition(g_collision[j].gameObjectIndex), r2)) {
						g_collision[i].ans = g_collision[j].ans = true;
						continue;
					}
				}

			}

			//ATK�n��collision���m�͓������Ă��Ă���������i�A�˂���Ɗ�{�d�Ȃ邩��j
			if (g_collision[i].layer == LAYER_ENEMY_ATK)continue;
			if (g_collision[i].layer == LAYER_PLAYER_ATK)continue;
			//HIT����p��collision�͍U���Ƃ̔���Ɏg������U���ȊO�͖���
			if (g_collision[i].layer == LAYER_ENEMY) continue;
			if (g_collision[i].layer == LAYER_PLAYER) continue;

			//���̑��̓����蔻��̔���
			if (g_collision[j].layer != g_collision[i].layer) continue;	// ���C���[����������r���Ȃ�
			if (g_collision[j].type != g_collision[i].type) continue;	// �^�C�v����������r���Ȃ�
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
				r2 *= 10;	//�����ڂƔ͈͂����킹���
				if (CollisionBC(GetPosition(g_collision[i].gameObjectIndex),r1,GetPosition(g_collision[i].gameObjectIndex),r2)) {
					g_collision[i].ans = g_collision[j].ans = true;
				}
			}
		}
	}
}

