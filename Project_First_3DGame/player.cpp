//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"
#include "input.h"
#include "camera.h"
#include "GameObject.h"
#include "collision.h"
#include "field.h"
#include "attack.h"
#include "UI.h"

#define MOVE_POWER	(0.06f)
#define DASH_POWER	(0.06f)

//�v���C���[�̏����ʒu�iY�͖ڐ��̍����j
#define PLAYER_OFFSET_X	(0.0f)
#define PLAYER_OFFSET_Y	(0.20f)
#define PLAYER_OFFSET_Z	(-10.0f)

//�v���C���[�̓����蔻��̑傫��
#define PLAYER_SIZE_X	(0.05f)
#define PLAYER_SIZE_Y	(0.20f)
#define PLAYER_SIZE_Z	(0.05f)




static int g_cameraIndex;
static int g_objIndex;
static int g_colIndex;
static int g_hitColIndex;

static int g_HP;			// PLAYER�̗̑�


void InitPlayer(void) {
	g_objIndex = SetGameObject();
	g_cameraIndex = GetCameraIndex();
	SetGameObjectParent(g_cameraIndex, g_objIndex);
	SetPosition(g_objIndex, XMFLOAT3(PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_OFFSET_Z));

	g_colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
	int index = GetColObjectIndex(g_colIndex);
	SetScale(index, XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	SetPosition(index, GetPosition(g_objIndex));

	//�����̂߂荞�݂���������
	while (GetColAnsUpdate(g_colIndex))
	{
		XMFLOAT3 pos = GetPosition(index);
		pos.y += 0.01f;
		SetPosition(index, pos);
	}
	SetPosition(g_objIndex, GetPosition(index));


	g_hitColIndex = SetCollision(LAYER_ENEMY_ATK, TYPE_BC);
	index = GetColObjectIndex(g_hitColIndex);
	SetScale(index, XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	SetPosition(index, GetPosition(g_objIndex));


	g_HP = 100;
}

void UninitPlayer(void) {

}

void UpdatePlayer(void) {
	XMFLOAT3 pos = GetPosition(g_objIndex);
	XMFLOAT3 bachPos = pos;
	XMFLOAT3 rot = GetRotation(g_objIndex);
	XMFLOAT3 scl = GetScale(g_objIndex);






	//�v���C���[�̈ړ�����
	{
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);
		if (GetInputPress(MOVE_FRONT)) {
			vec.x += sinf(rot.x);
			vec.z += cosf(rot.x);
		}

		if (GetInputPress(MOVE_BACK)) {
			vec.x -= sinf(rot.x);
			vec.z -= cosf(rot.x);
		}

		if (GetInputPress(MOVE_LEFT)) {
			vec.z += sinf(rot.x);
			vec.x -= cosf(rot.x);
		}

		if (GetInputPress(MOVE_RIGHT)) {
			vec.x += cosf(rot.x);
			vec.z -= sinf(rot.x);
		}

		//���̃v���[���ňړ����������Ă���A�΂߈ړ��̑��x�𒲐�
		if (ComparisonXMFLOAT3(vec, XMFLOAT3(0.0f, 0.0f, 0.0f))) {
			vec = NormalizeXMFLOAT3(vec);
			// �_�b�V��
			if (GetInputPress(MOVE_DASH)) {
				vec = MulXMFLOAT3(vec, SetXMFLOAT3(MOVE_POWER+DASH_POWER));
			}
			else {
				vec = MulXMFLOAT3(vec, SetXMFLOAT3(MOVE_POWER));
			}

			pos = AddXMFLOAT3(pos, vec);
			SetPosition(g_objIndex, pos);
		}




		DllRotation(GetLookInput(0), &rot, 0.03f);

		//�J�������c�����Ɉ��]���Ȃ��悤�ɐ�������
		rot.z = Clamp(rot.z, -XM_PI / 2.0f, XM_PI / 2.0f);

		SetRotation(g_objIndex, rot);
	}


	//�U������
	{

		if(GetInputPress(AIMING)) {
			UI_ELEMENT* ui = GetUI(ATK_MAHOUZIN);
			ui->use = true;
		}
		else {
			UI_ELEMENT* ui = GetUI(ATK_MAHOUZIN);
			ui->use = false;
			if (GetInputPress(ATK_1)) {
				
				SetAttack(ATK_PLAYER_1, g_cameraIndex);
			}
		}
		if (GetInputPress(ATK_2)) {
			SetAttack(ATK_PLAYER_2, g_cameraIndex);
		}
	}

	//�����蔻��
	{
		//�U���ɑ΂��铖���蔻��̍X�V
		SetPosition(GetColObjectIndex(g_hitColIndex), pos);
		if (GetColAns(g_hitColIndex)) {
			g_HP--;		//�U���̎�ނɂ����炸�P�_���[�W�i�����U���͏d�˂�΂ǂ��ɂ��Ȃ�j
		}

		if (g_HP <= 0) {
			SetIsClear(false);
			SetMode(MODE_RESULT);
		}


		//�ړ��ɑ΂��铖���蔻��̍X�V
		int index = GetColObjectIndex(g_colIndex);
		//XMFLOAT3 pos = GetPosition(g_objIndex);
		SetPosition(index, pos);


		if (!GetColAns(g_colIndex)) {
			pos.y -= 0.01f;
			SetPosition(index, pos);
			if (GetColAnsUpdate(g_colIndex)) {
				pos.y += 0.01f;
				SetPosition(index, pos);
			}
			SetPosition(g_objIndex, pos);
		}


		if (GetColAnsUpdate(g_colIndex)) {
			SetPosition(g_objIndex, bachPos);

		}

	}


	//�J�����̍X�V
	SetGameObjectZERO(g_cameraIndex);	//�e����݂������O�ɂ���
	SetPosition(g_cameraIndex, XMFLOAT3(0.0f, 2.5f, 0.0f));	//�e����݂����W��������������


	//�V�[���J��
	if (g_HP <= 0) SetMode(MODE_RESULT);

}
void DrawPlayer(void) {

}