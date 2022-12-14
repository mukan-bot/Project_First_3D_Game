//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "GameObject.h"

#define VALUM_MOVE (0.3f)

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
		if (GetInputPress(MOVE_FRONT)) {
			OutputDebug("�O�Ɉړ�\n");
			pos.x += sinf(rot.x) * VALUM_MOVE;
			pos.z += cosf(rot.x) * VALUM_MOVE;
		}

		if (GetInputPress(MOVE_BACK)) {
			OutputDebug("���Ɉړ�\n");
			pos.x -= sinf(rot.x) * VALUM_MOVE;
			pos.z -= cosf(rot.x) * VALUM_MOVE;
		}

		if (GetInputPress(MOVE_LEFT)) {
			OutputDebug("���Ɉړ�\n");
			pos.z += sinf(rot.x) * VALUM_MOVE;
			pos.x -= cosf(rot.x) * VALUM_MOVE;
		}

		if (GetInputPress(MOVE_RIGHT)) {
			OutputDebug("�E�Ɉړ�\n");
			pos.x += cosf(rot.x) * VALUM_MOVE;
			pos.z -= sinf(rot.x) * VALUM_MOVE;
		}
		SetPosition(g_cameraIndex, pos);


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