//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "GameObject.h"

#define VALUM_MOVE (0.03f)

static int g_cameraIndex;

float g_spd = 0.0f;
float g_dir = 0.0f;

void InitPlayer(void) {
	g_cameraIndex = GetCameraIndex();
}

void UninitPlayer(void) {

}

void UpdatePlayer(void) {
	XMFLOAT3 pos = GetPosition(g_cameraIndex);
	XMFLOAT3 rot = GetRotation(g_cameraIndex);
	XMFLOAT3 scl = GetScale(g_cameraIndex);



	if (GetInputPress(MOVE_FRONT)) {
		OutputDebug("ëOÇ…à⁄ìÆ\n");
		pos.x += sinf(rot.x) * VALUM_MOVE;
		pos.z += cosf(rot.x) * VALUM_MOVE;
	}
	if (GetInputPress(MOVE_BACK)) {
		OutputDebug("å„ÇÎÇ…à⁄ìÆ\n");
		pos.x -= sinf(rot.x) * VALUM_MOVE;
		pos.z -= cosf(rot.x) * VALUM_MOVE;
	}
	if (GetInputPress(MOVE_LEFT)) {
		OutputDebug("ç∂Ç…à⁄ìÆ\n");
		pos.z += sinf(rot.x) * VALUM_MOVE;
		pos.x -= cosf(rot.x) * VALUM_MOVE;

	}
	if (GetInputPress(MOVE_RIGHT)) {
		OutputDebug("âEÇ…à⁄ìÆ\n");
		pos.x += cosf(rot.x) * VALUM_MOVE;
		pos.z -= sinf(rot.x) * VALUM_MOVE;

	}

	SetPosition(g_cameraIndex, pos);


	DllRotation(GetLookInput(0), &rot, 0.03f);
	SetRotation(g_cameraIndex, rot);


}
void DrawPlayer(void) {

}