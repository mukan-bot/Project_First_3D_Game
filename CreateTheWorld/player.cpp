//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "GameObject.h"

static int g_cameraIndex;

void InitPlayer(void) {
	g_cameraIndex = GetCameraIndex();
}
void UninitPlayer(void) {

}
void UpdatePlayer(void) {
	XMFLOAT3 pos = GetPosition(g_cameraIndex);
	XMFLOAT3 rot = GetRotation(g_cameraIndex);
	XMFLOAT3 scl = GetScale(g_cameraIndex);

	DllRotation(GetLookInput(0), &rot, 0.03f);
	SetRotation(g_cameraIndex, rot);

	if (GetInputPress(MOVE_FRONT)) {
		OutputDebug("前に移動\n");
		pos.z += 0.03f;
	}
	if (GetInputPress(MOVE_BACK)) {
		OutputDebug("後ろに移動\n");
		pos.z -= 0.03f;
	}
	if (GetInputPress(MOVE_LEFT)) {
		OutputDebug("左に移動\n");
		pos.x -= 0.03f;
	}
	if (GetInputPress(MOVE_RIGHT)) {
		OutputDebug("右に移動\n");
		pos.x += 0.03f;
	}
	SetPosition(g_cameraIndex, pos);


}
void DrawPlayer(void) {

}