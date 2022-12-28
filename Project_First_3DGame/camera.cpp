//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "camera.h"
#include "renderer.h"

#include "input.h"
#include "input_D.h"

//マクロ定義
#define	POS_X_CAM			(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM			(50.0f)			// カメラの初期位置(Y座標)
#define	POS_Z_CAM			(-140.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

//グローバル変数
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
	// ビューマトリックス設定
	XMMATRIX mtxView;
	XMMATRIX world, rot, trans;

	XMFLOAT3 objectRotate = GetRotation(g_gameObjectIndex);
	XMFLOAT3 objectPosition = GetPosition(g_gameObjectIndex);



	rot = XMMatrixRotationRollPitchYaw(objectRotate.z, objectRotate.x, objectRotate.y);
	trans = XMMatrixTranslation(objectPosition.x, objectPosition.y, objectPosition.z);
	world = rot * trans;

	mtxView = XMMatrixInverse(nullptr, world);

	SetViewMatrix(& mtxView);

	//プロジェクションマトリックス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f,(float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
	SetProjectionMatrix(&projectionMatrix);

	SetShaderCamera(objectPosition);
}


int GetCameraIndex(void) { return g_gameObjectIndex; };