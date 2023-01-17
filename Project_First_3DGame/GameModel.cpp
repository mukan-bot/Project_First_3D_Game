//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "GameModel.h"


//�}�N����`
#define MAX_MODEL	(512)	//�Ƃ肠����256�ɂ��Ă���

struct GameModel{
	bool is_load;				// ���[�h����Ă��邩�i���f�����j
	int is_fuchi;				// ���������邩
	int gameObjectIndex;		// Pos�Ƃ�Rot�AScl����������
	XMFLOAT3 ofsetScale;		// Scl�̒����p
	CULL_MODE cullMode;			// �J�����O���[�h
	XMFLOAT4X4 mtxWorld;		// 
	DX11_MODEL model;			// 
	bool use;					// GameModel���g���Ă��邩
	D3D11_FILL_MODE fillMode;	// �h����ǂ����邩
};



//�O���[�o���ϐ�
GameModel g_gameModel[MAX_MODEL];



//=============================================================================
// ��������
//=============================================================================
void InitGameModel(void){
	//�Q�[�����f���̏�����
	for (int i = 0; i < MAX_MODEL; i++) {
		g_gameModel[i].gameObjectIndex = -1;
		g_gameModel[i].is_load = false;
		g_gameModel[i].is_fuchi = 0;
		g_gameModel[i].cullMode = CULL_MODE_NUM;
		g_gameModel[i].ofsetScale = SetXMFLOAT3(1.0f);
		g_gameModel[i].use = false;
	}
}



//=============================================================================
// �I������
//=============================================================================
void UninitGameModel (void){
	// ���f���̉������
	for (int i = 0; i < MAX_MODEL; i++) {
		{
			UnloadModel(&g_gameModel[i].model);
			g_gameModel[i] .is_load = false;
		}
		if (g_gameModel[i].use) {
			g_gameModel[i].use = false;
		}
	}
}



//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameModel(void){
	for (int i = 0; i < MAX_MODEL; i++) {
		// �g���Ă��Ȃ��Ȃ珈�����΂�
		if (!g_gameModel[i].use) continue;

		// �K�v�ȏ�������
		XMFLOAT3 pos = GetPosition(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 rot = GetRotation(g_gameModel[i].gameObjectIndex);
		XMFLOAT3 scl = GetScale(g_gameModel[i].gameObjectIndex);
		// �X�P�[���𒲐�
		scl = MulXMFLOAT3(scl, g_gameModel[i].ofsetScale);

		// �h���ύX
		SetPixelFill(g_gameModel[i].fillMode);

#ifdef _DEBUG
		// �f�o�b�N�ł̂݃��C���[�t���[���ł��ׂĂ�\���ł���悤�ɂ���
		if (GetInputPress(MOVE_JUMP)) {
			SetPixelFill(D3D11_FILL_WIREFRAME);
		}
#endif // _DEBUG

		// �J�����O
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

		XMStoreFloat4x4(&g_gameModel[i].mtxWorld, mtxWorld);


		// ���f���`��
		DrawModel(&g_gameModel[i].model);

	}

	// ���C���[�t���[������߂�
	SetPixelFill(D3D11_FILL_SOLID);

	//���ݒ�߂�
	SetFuchi(0);

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);


}





int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi,CULL_MODE cullMode) {
	int ans = -1;

	for (int i = 0; i < MAX_MODEL; i++) {
		//�g���Ă���̂Ȃ��΂�
		if (g_gameModel[i].use) continue;
		if (strcmp(modelPath, "NO") != 0) {	//���f�����g�p���Ȃ����iGetModel�Ŋ撣�鎞�j
			LoadModel(modelPath, &g_gameModel[i].model);
			g_gameModel[i].is_load = true;
		}

		g_gameModel[i].gameObjectIndex = gameObjectIndex;
		g_gameModel[i].is_fuchi = fuchi;
		g_gameModel[i].cullMode = cullMode;

		g_gameModel[i].fillMode = D3D11_FILL_SOLID;

		g_gameModel[i].use = true;

		ans = i;
		break;
	}
#ifdef _DEBUG
	if (ans == -1) {
		OutputDebug("SetGameModel��-1���Ԃ���܂���");
	}
#endif // _DEBUG

	return ans;
}

void DelGameModel(int index) {
	// �w�肳�ꂽ���f�����ǂݍ��܂�Ă�����폜
	if (g_gameModel[index].is_load)
	{
		UnloadModel(&g_gameModel[index].model);
		g_gameModel[index].is_load = false;
	}
	// use����������
	g_gameModel[index].use = false;
}


void SetGameModelScale(int index, XMFLOAT3 scale) {
	g_gameModel[index].ofsetScale = scale;
}

DX11_MODEL* GetModel(int index) {
	return &g_gameModel[index].model;
}

void SetGameModeFill(int index, D3D11_FILL_MODE model){
	g_gameModel[index].fillMode = model;
}