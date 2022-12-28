//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "camera.h"
#include "renderer.h"

#include "input.h"
#include "input_D.h"

//�}�N����`
#define	POS_X_CAM			(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM			(50.0f)			// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM			(-140.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

//�O���[�o���ϐ�
static int g_gameObjectIndex;

void InitCameraM_Game(void) {
	g_gameObjectIndex = SetGameObject();
}


void UpdateCamera(void) {
	int cindex = GetCameraIndex();
	XMFLOAT3 cpos = GetPosition(cindex);
	XMFLOAT3 crot = GetRotation(cindex);


}



void DrawCamera(void) {
	// �r���[�}�g���b�N�X�ݒ�
	XMMATRIX mtxView;
	XMMATRIX world, rot, trans;

	XMFLOAT3 objectRotate = GetRotation(g_gameObjectIndex);
	XMFLOAT3 objectPosition = GetPosition(g_gameObjectIndex);



	rot = XMMatrixRotationRollPitchYaw(objectRotate.z, objectRotate.x, objectRotate.y);
	trans = XMMatrixTranslation(objectPosition.x, objectPosition.y, objectPosition.z);
	world = rot * trans;

	mtxView = XMMatrixInverse(nullptr, world);

	SetViewMatrix(& mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�ݒ�
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f,(float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
	SetProjectionMatrix(&projectionMatrix);

	SetShaderCamera(objectPosition);
}


int GetCameraIndex(void) { return g_gameObjectIndex; };