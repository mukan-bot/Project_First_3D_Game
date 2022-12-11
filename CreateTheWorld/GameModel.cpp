//=============================================================================
//
// ���f������ [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "GameModel.h"


//�}�N����`
#define MAX_MODEL	(256)	//�Ƃ肠����256�ɂ��Ă���

struct GameModel{
	bool is_load;
	DX11_MODEL model;
	int is_fuchi;
	CULL_MODE cullMode;
	int gameObjectIndex;
	bool use;
};



//�O���[�o���ϐ�
GameModel g_gameModel[MAX_MODEL];


//=============================================================================
// ��������
//=============================================================================
void InitGameModel(void){
	for (int i = 0; i < MAX_MODEL; i++) {
		g_gameModel[i].gameObjectIndex = -1;
		g_gameModel[i].is_load = false;
		g_gameModel[i].is_fuchi = 0;
		g_gameModel[i].cullMode = CULL_MODE_NUM;
		g_gameModel[i].use = false;
	}
}



//=============================================================================
// �I������
//=============================================================================
void UninitGameModel (void)
{
	// ���f���̉������
	for (int i = 0; i < MAX_MODEL; i++) {
		if (g_gameModel[i].is_load)
		{
			UnloadModel(&g_gameModel[i] .model);
			g_gameModel[i] .is_load = false;
		}
	}
}




//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameModel(void)
{
	for (int i = 0; i < MAX_MODEL; i++) {
		if (!g_gameModel[i].use) continue;

		XMFLOAT3 pos = GetPosition(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 rot = GetRotation(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 scl = GetScale(g_gameModel[i].gameObjectIndex);



		// �J�����O����
		SetCullingMode(g_gameModel[i].cullMode);

		//���ݒ�
		SetFuchi(g_gameModel[i].is_fuchi);


		XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(scl.x, scl.y, scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y + XM_PI, rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(& mtxWorld, mtxWorld);	//TODO:model�P�ʂ�mtxWorld���A�ڂ�����player.cpp����


		// ���f���`��
		DrawModel(&g_gameModel[i].model);

		//���ݒ�߂�
		SetFuchi(0);

		// �J�����O�ݒ��߂�
		SetCullingMode(CULL_MODE_BACK);

	}
}





int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi,CULL_MODE cullMode) {
	int ans;
	for (int i = 0; i < MAX_MODEL; i++) {
		if (g_gameModel[i].use) continue;

		LoadModel(modelPath, &g_gameModel[i].model);
		g_gameModel[i].is_load = true;

		g_gameModel[i].gameObjectIndex = gameObjectIndex;
		g_gameModel[i].is_fuchi = fuchi;
		g_gameModel[i].cullMode = cullMode;

		g_gameModel[i].use = false;

		ans = i;
		break;
	}
	return ans;
}

void DelGameModel(int index) {
	if (g_gameModel[index].is_load)
	{
		UnloadModel(&g_gameModel[index].model);
		g_gameModel[index].is_load = false;
	}
	g_gameModel[index].use = false;
}