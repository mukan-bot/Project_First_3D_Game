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

#define MOVE_POWER	(0.03f)
#define DASH_POWER	(0.03f)

//プレイヤーの初期位置（Yは目線の高さ）
#define PLAYER_OFFSET_X	(0.0f)
#define PLAYER_OFFSET_Y	(0.20f)
#define PLAYER_OFFSET_Z	(-10.0f)

//プレイヤーの当たり判定の大きさ
#define PLAYER_SIZE_X	(0.05f)
#define PLAYER_SIZE_Y	(0.20f)
#define PLAYER_SIZE_Z	(0.05f)

static int g_cameraIndex;
static int g_objIndex;
static int g_colIndex;


void InitPlayer(void) {
	g_objIndex = SetGameObject();
	g_cameraIndex = GetCameraIndex();
	SetGameObjectParent(g_cameraIndex, g_objIndex);
	SetPosition(g_objIndex, XMFLOAT3(PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_OFFSET_Z));

	g_colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
	int index = GetColObjectIndex(g_colIndex);
	SetScale(index, XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	SetPosition(index, GetPosition(g_objIndex));

	//初期のめり込みを解消する
	while (GetColAnsUpdate(g_colIndex))
	{
		XMFLOAT3 pos = GetPosition(index);
		pos.y += 0.01f;
		SetPosition(index, pos);
	}
	SetPosition(g_objIndex, GetPosition(index));

}

void UninitPlayer(void) {

}

void UpdatePlayer(void) {
	XMFLOAT3 pos = GetPosition(g_objIndex);
	XMFLOAT3 bachPos = pos;
	XMFLOAT3 rot = GetRotation(g_objIndex);
	XMFLOAT3 scl = GetScale(g_objIndex);






	//プレイヤーの移動処理
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

		//このプレームで移動したかしてたら、斜め移動の速度を調節
		if (ComparisonXMFLOAT3(vec, XMFLOAT3(0.0f, 0.0f, 0.0f))) {
			vec = NormalizeXMFLOAT3(vec);
			// ダッシュ
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

		//カメラが縦方向に一回転しないように制限する
		rot.z = Clamp(rot.z, -XM_PI / 2.0f, XM_PI / 2.0f);

		SetRotation(g_objIndex, rot);
	}


	//攻撃処理
	{

	}

	//当たり判定
	{

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


		//XMFLOAT3 playerPos = GetPosition(g_objIndex);
		//int Count;
		//XMFLOAT3 hit;
		//XMFLOAT3 normal;
		//bool is_Hit = false;
		//SET_OBJECT* field = GetFieldObject(&Count);

		//for (int i = 0; i < Count; i++) {
		//	if (field[i].gameObjectIndex == -1) continue;

		//	XMFLOAT3 xp0, xp1, xp2, xpos, xvec;
		//	XMFLOAT3 pos = GetPosition(field[i].gameObjectIndex);
		//	XMFLOAT3 size = GetScale(field[i].gameObjectIndex);
		//	size = DivXMFLOAT3(size, SetXMFLOAT3(2.0f));
		//	xp0 = AddXMFLOAT3(pos, size);
		//	xp1 = SubXMFLOAT3(pos, size);
		//	size.x *= -1;
		//	xp2 = AddXMFLOAT3(pos, size);
		//	is_Hit = RayCast(xp0, xp1, xp2, playerPos, XMFLOAT3(0.0f, PLAYER_SIZE_Y, 0.0f), &hit, &normal);
		//	OutputDebug("");
		//	size.x *= -1;
		//	size.z *= -1;
		//	xp2 = AddXMFLOAT3(pos, size);
		//	is_Hit = RayCast(xp0, xp1, xp2, playerPos, XMFLOAT3(0.0f, PLAYER_SIZE_Y, 0.0f), &hit, &normal);
		//	OutputXMFLOAT3Debug("hit",hit);
		//	if (is_Hit) {
		//		XMFLOAT3 pos = playerPos;
		//		pos.y = PLAYER_SIZE_Y - hit.y;
		//		SetPosition(g_objIndex, pos);
		//		break;
		//	}
		//}

		//if (!is_Hit) {
		//	playerPos.y -= 0.01f;
		//	SetPosition(g_objIndex, playerPos);
		//}
		//





	}


	//カメラの更新
	SetGameObjectZERO(g_cameraIndex);	//親からみた情報を０にする
	SetPosition(g_cameraIndex, XMFLOAT3(0.0f, 2.5f, 0.0f));	//親からみた座標を少し高くする

}
void DrawPlayer(void) {

}