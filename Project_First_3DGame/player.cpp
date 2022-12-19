//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"
#include "input.h"
#include "camera.h"
#include "GameObject.h"

#define MOVE_POWER (0.03f)

//�v���C���[�̏����ʒu�iY�͖ڐ��̍����j
#define PLAYER_OFFSET_X	(0.0f)
#define PLAYER_OFFSET_Y	(5.0f)
#define PLAYER_OFFSET_Z	(-10.0f)


static int g_cameraIndex;

float g_spd = 0.0f;
float g_dir = 0.0f;

void InitPlayer(void) {
	g_cameraIndex = GetCameraIndex();
	SetPosition(g_cameraIndex, XMFLOAT3(PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_OFFSET_Z));
}

void UninitPlayer(void) {

}

void UpdatePlayer(void) {
	XMFLOAT3 pos = GetPosition(g_cameraIndex);
	XMFLOAT3 rot = GetRotation(g_cameraIndex);
	XMFLOAT3 scl = GetScale(g_cameraIndex);

	//�v���C���[�̈ړ�����
	{
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);
		if (GetInputPress(MOVE_FRONT)) {
			OutputDebug("�O�Ɉړ�\n");
			vec.x += sinf(rot.x);
			vec.z += cosf(rot.x);
		}

		if (GetInputPress(MOVE_BACK)) {
			OutputDebug("���Ɉړ�\n");
			vec.x -= sinf(rot.x);
			vec.z -= cosf(rot.x);
		}

		if (GetInputPress(MOVE_LEFT)) {
			OutputDebug("���Ɉړ�\n");
			vec.z += sinf(rot.x);
			vec.x -= cosf(rot.x);
		}

		if (GetInputPress(MOVE_RIGHT)) {
			OutputDebug("�E�Ɉړ�\n");
			vec.x += cosf(rot.x);
			vec.z -= sinf(rot.x);
		}

		//���̃v���[���ňړ����������Ă���A�΂߈ړ��̑��x�𒲐�
		if (ComparisonXMFLOAT3(vec, XMFLOAT3(0.0f, 0.0f, 0.0f))) {
			vec = NormalizeXMFLOAT3(vec);
			vec = MulXMFLOAT3(vec, XMFLOAT3(MOVE_POWER, MOVE_POWER, MOVE_POWER));

			pos = AddXMFLOAT3(pos, vec);
			SetPosition(g_cameraIndex, pos);
		}




		DllRotation(GetLookInput(0), &rot, 0.03f);

		//�J�������c�����Ɉ��]���Ȃ��悤�ɐ�������
		rot.z = Clamp(rot.z, -XM_PI / 2.0f, XM_PI / 2.0f);

		SetRotation(g_cameraIndex, rot);
	}


	//�U������
	{

	}



}
void DrawPlayer(void) {

}