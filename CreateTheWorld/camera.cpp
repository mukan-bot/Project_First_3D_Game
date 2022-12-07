#include "main.h"

//�}�N����`
#define	POS_X_CAM			(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM			(50.0f)			// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM			(-140.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

//�O���[�o���ϐ�
int g_gameObjectIndex = SetGameObject();

void DrawCamera(void) {
	// �r���[�}�g���b�N�X�ݒ�
	XMMATRIX mtxView;
	XMMATRIX world, rot, trans;

	XMFLOAT3 objectRotate = GetRotation(g_gameObjectIndex);
	XMFLOAT3 objectPosition = GetPosition(g_gameObjectIndex);

	rot = XMMatrixRotationRollPitchYaw(objectRotate.z, objectRotate.x, objectRotate.y);
	trans = XMMatrixTranslation(objectPosition.x, objectPosition.y, objectPosition.z);
	world = rot * trans;
	XMMatrixInverse(&mtxView, NULL,&world)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mtxView = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&g_Camera.at), XMLoadFloat3(&g_Camera.up));
	SetViewMatrix(&mtxView);
	XMStoreFloat4x4(&g_Camera.mtxView, mtxView);

	XMMATRIX mtxInvView;
	mtxInvView = XMMatrixInverse(nullptr, mtxView);
	XMStoreFloat4x4(&g_Camera.mtxInvView, mtxInvView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	XMMATRIX mtxProjection;
	mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&mtxProjection);
	XMStoreFloat4x4(&g_Camera.mtxProjection, mtxProjection);

	SetShaderCamera(g_Camera.pos);
}