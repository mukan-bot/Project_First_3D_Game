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
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/Kirby_Body.obj"			// �ǂݍ��ރ��f����
#define	MODEL_PLAYER_LEG_L	"data/MODEL/Kirby_Leg_L.obj"			// �ǂݍ��ރ��f����
#define	MODEL_PLAYER_LEG_R	"data/MODEL/Kirby_Leg_R.obj"			// �ǂݍ��ރ��f����
#define	MODEL_PLAYER_ARM_L	"data/MODEL/Kirby_Arm_L.obj"			// �ǂݍ��ރ��f����
#define	MODEL_PLAYER_ARM_R	"data/MODEL/Kirby_Arm_R.obj"			// �ǂݍ��ރ��f����

#define	VALUE_MOVE			(2.0f)							// �ړ���
#define	VALUE_ROTATE		(XM_PI * 0.02f)					// ��]��

#define PLAYER_SHADOW_SIZE	(1.0f)							// �e�̑傫��
#define PLAYER_OFFSET_Y		(5.0f)							// �v���C���[�̑��������킹��

#define PLAYER_PARTS_MAX	(4)								// �v���C���[�̃p�[�c�̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER		g_Player;						// �v���C���[

static PLAYER		g_Parts[PLAYER_PARTS_MAX];		// �v���C���[�̃p�[�c�p


// �v���C���[�̊K�w�A�j���[�V�����f�[�^
// �v���C���[�̓������E�ɓ������Ă���A�j���f�[�^
static INTERPOLATION_DATA move_tbl_right[] = {	// pos, rot, scl, frame

	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI / 5, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI / 5, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA move_tbl_left[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI / 5, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI / 5, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA move_tbl_IdleParts[]{
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};
static INTERPOLATION_DATA move_tbl_IdleMain[]{
	{ XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),    XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
};

static INTERPOLATION_DATA* g_MoveTblAdr[] =
{
	move_tbl_right,
	move_tbl_left,
	move_tbl_IdleParts,
	move_tbl_IdleMain,

};



//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LoadModel(MODEL_PLAYER, &g_Player.model);
	g_Player.load = true;

	g_Player.pos = { 0.0f, PLAYER_OFFSET_Y, 0.0f };
	g_Player.rot = { 0.0f, 0.0f, 0.0f };
	g_Player.scl = { 0.05f, 0.05f, 0.05f };

	g_Player.spd = 0.0f;			// �ړ��X�s�[�h�N���A
	g_Player.size = PLAYER_SIZE;	// �����蔻��̑傫��

	g_Player.use = true;

	// �����Ńv���C���[�p�̉e���쐬���Ă���
	XMFLOAT3 pos = g_Player.pos;
	pos.y -= (PLAYER_OFFSET_Y - 0.1f);
	//          ��
	//        ���̃����o�[�ϐ������������e��Index�ԍ�
	// �K�w�A�j���[�V�����p�̏���������
	g_Player.parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
	g_Player.time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
	g_Player.tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
	g_Player.tblMax = 0;			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g
	g_Parts[0].tblMax = 0;			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g




	// �p�[�c�̏�����
	for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
		g_Parts[i].use = false;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_Parts[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Parts[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_Parts[i].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

		// �e�q�֌W
		g_Parts[i].parent = &g_Player;		// �� �����ɐe�̃A�h���X������

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
		g_Parts[i].time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
		g_Parts[i].tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
		g_Parts[i].tblMax = 0;			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

		// �p�[�c�̓ǂݍ��݂͂܂����Ă��Ȃ�
		g_Parts[i].load = 0;
	}


	g_Parts[0].use = true;
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Parts[0].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[0].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[0].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// �e�q�֌W
	g_Parts[0].parent = &g_Player;		// �� �����ɐe�̃A�h���X������

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
	g_Parts[0].time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
	g_Parts[0].tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
	g_Parts[0].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

	// �p�[�c�̓ǂݍ���
	LoadModel(MODEL_PLAYER_LEG_L, &g_Parts[0].model);
	g_Parts[0].load = true;



	g_Parts[1].use = true;
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Parts[1].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[1].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[1].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// �e�q�֌W
	g_Parts[1].parent = &g_Player;		// �� �����ɐe�̃A�h���X������

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
	g_Parts[1].time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
	g_Parts[1].tblNo = 1;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
	g_Parts[1].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

	// �p�[�c�̓ǂݍ���
	LoadModel(MODEL_PLAYER_LEG_R, &g_Parts[1].model);
	g_Parts[1].load = true;


	g_Parts[2].use = true;
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Parts[2].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[2].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[2].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// �e�q�֌W
	g_Parts[2].parent = &g_Player;		// �� �����ɐe�̃A�h���X������

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
	g_Parts[2].time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
	g_Parts[2].tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
	g_Parts[2].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

	// �p�[�c�̓ǂݍ���
	LoadModel(MODEL_PLAYER_ARM_L, &g_Parts[2].model);
	g_Parts[2].load = true;



	g_Parts[3].use = true;
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Parts[3].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[3].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Parts[3].scl = XMFLOAT3(0.10f, 0.10f, 0.10f);

	// �e�q�֌W
	g_Parts[3].parent = &g_Player;		// �� �����ɐe�̃A�h���X������

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
	g_Parts[3].time = 0.0f;			// ���`��ԗp�̃^�C�}�[���N���A
	g_Parts[3].tblNo = 1;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
	g_Parts[3].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

	// �p�[�c�̓ǂݍ���
	LoadModel(MODEL_PLAYER_ARM_R, &g_Parts[3].model);
	g_Parts[3].load = true;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// ���f���̉������
	if (g_Player.load)
	{
		UnloadModel(&g_Player.model);
		g_Player.load = false;
	}
	// ���f���̉������
	for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
		if (g_Parts[i].load)
		{
			UnloadModel(&g_Parts[i].model);
			g_Parts[i].load = false;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{


#ifdef _DEBUG
#endif


	//	// Key���͂���������ړ���������
	if (g_Player.spd > 0.0f)
	{
		//�v���C���[�̃A�j���[�V�������A�C�h���ɂ���
		g_Player.tblNo = 0;
		g_Player.tblMax = 0;

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
		g_Parts[0].tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
		g_Parts[0].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
		g_Parts[1].tblNo = 1;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
		g_Parts[1].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
		g_Parts[2].tblNo = 0;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
		g_Parts[2].tblMax = sizeof(move_tbl_right) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ��̏�����
		g_Parts[3].tblNo = 1;			// �Đ�����s���f�[�^�e�[�u��No���Z�b�g
		g_Parts[3].tblMax = sizeof(move_tbl_left) / sizeof(INTERPOLATION_DATA);			// �Đ�����s���f�[�^�e�[�u���̃��R�[�h�����Z�b�g

		//�v���C���[�̈ړ�

		
		// ���͂̂����������փv���C���[���������Ĉړ�������
		g_Player.pos.x -= sinf(g_Player.rot.y) * g_Player.spd;
		g_Player.pos.z -= cosf(g_Player.rot.y) * g_Player.spd;
	}

	else {
		//�v���C���[�̃A�j���[�V�������A�C�h���ɂ���
		g_Player.tblNo = 3;
		g_Player.tblMax = sizeof(move_tbl_IdleMain) / sizeof(INTERPOLATION_DATA);
		for (int i = 0; i < PLAYER_PARTS_MAX; i++) {
			g_Parts[i].time = 0.0f;
			g_Parts[i].tblNo = 3;
			g_Parts[i].tblMax = sizeof(move_tbl_IdleParts) / sizeof(INTERPOLATION_DATA);
		}
	}

	g_Player.spd *= 0.5f;


	// �K�w�A�j���[�V����
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		// �g���Ă���Ȃ珈������
		if ((g_Parts[i].use == true) && (g_Parts[i].tblMax > 0))
		{	// ���`��Ԃ̏���
			int nowNo = (int)g_Parts[i].time;			// �������ł���e�[�u���ԍ������o���Ă���
			int maxNo = g_Parts[i].tblMax;				// �o�^�e�[�u�����𐔂��Ă���
			int nextNo = (nowNo + 1) % maxNo;			// �ړ���e�[�u���̔ԍ������߂Ă���
			INTERPOLATION_DATA* tbl = g_MoveTblAdr[g_Parts[i].tblNo];	// �s���e�[�u���̃A�h���X���擾

			XMVECTOR nowPos = XMLoadFloat3(&tbl[nowNo].pos);	// XMVECTOR�֕ϊ�
			XMVECTOR nowRot = XMLoadFloat3(&tbl[nowNo].rot);	// XMVECTOR�֕ϊ�
			XMVECTOR nowScl = XMLoadFloat3(&tbl[nowNo].scl);	// XMVECTOR�֕ϊ�

			XMVECTOR Pos = XMLoadFloat3(&tbl[nextNo].pos) - nowPos;	// XYZ�ړ��ʂ��v�Z���Ă���
			XMVECTOR Rot = XMLoadFloat3(&tbl[nextNo].rot) - nowRot;	// XYZ��]�ʂ��v�Z���Ă���
			XMVECTOR Scl = XMLoadFloat3(&tbl[nextNo].scl) - nowScl;	// XYZ�g�嗦���v�Z���Ă���

			float nowTime = g_Parts[i].time - nowNo;	// ���ԕ����ł��鏭�������o���Ă���

			Pos *= nowTime;								// ���݂̈ړ��ʂ��v�Z���Ă���
			Rot *= nowTime;								// ���݂̉�]�ʂ��v�Z���Ă���
			Scl *= nowTime;								// ���݂̊g�嗦���v�Z���Ă���

			// �v�Z���ċ��߂��ړ��ʂ����݂̈ړ��e�[�u��XYZ�ɑ����Ă��遁�\�����W�����߂Ă���
			XMStoreFloat3(&g_Parts[i].pos, nowPos + Pos);

			// �v�Z���ċ��߂���]�ʂ����݂̈ړ��e�[�u���ɑ����Ă���
			XMStoreFloat3(&g_Parts[i].rot, nowRot + Rot);

			// �v�Z���ċ��߂��g�嗦�����݂̈ړ��e�[�u���ɑ����Ă���
			XMStoreFloat3(&g_Parts[i].scl, nowScl + Scl);

			// frame���g�Ď��Ԍo�ߏ���������
			g_Parts[i].time += 1.0f / tbl[nowNo].frame;	// ���Ԃ�i�߂Ă���
			if ((int)g_Parts[i].time >= maxNo)			// �o�^�e�[�u���Ō�܂ňړ��������H
			{
				g_Parts[i].time -= maxNo;				// �O�ԖڂɃ��Z�b�g�������������������p���ł���
			}

		}

	}






#ifdef _DEBUG	// �f�o�b�O����\������
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	//�����
	SetFuchi(1);


	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// �X�P�[���𔽉f
	mtxScl = XMMatrixScaling(g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(g_Player.rot.x, g_Player.rot.y + XM_PI, g_Player.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&mtxWorld);

	XMStoreFloat4x4(&g_Player.mtxWorld, mtxWorld);


	// ���f���`��
	DrawModel(&g_Player.model);


	//MEMO:�����ŊK�w�A�j���[�V���������Ă���B
	// �p�[�c�̊K�w�A�j���[�V����
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_Parts[i].scl.x, g_Parts[i].scl.y, g_Parts[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_Parts[i].rot.x, g_Parts[i].rot.y, g_Parts[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_Parts[i].pos.x, g_Parts[i].pos.y, g_Parts[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		if (g_Parts[i].parent != NULL)	// �q����������e�ƌ�������
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_Parts[i].parent->mtxWorld));
			// ��
			// g_Player.mtxWorld���w���Ă���
		}

		//�����̎q���̃p�[�c�̂��߂Ɂi�`��Ŏg�����[���h�j
		XMStoreFloat4x4(&g_Parts[i].mtxWorld, mtxWorld);

		// �g���Ă���Ȃ珈������B�����܂ŏ������Ă��闝�R�͑��̃p�[�c�����̃p�[�c���Q�Ƃ��Ă���\�������邩��B
		if (g_Parts[i].use == false) continue;

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);


		// ���f���`��
		DrawModel(&g_Parts[i].model);



	}

	//�����
	SetFuchi(0);

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player;
}

