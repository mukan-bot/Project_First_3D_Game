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

#define MOVE_POWER	(0.12f)
#define DASH_POWER	(0.12f)

//プレイヤーの初期位置（Yは目線の高さ）
#define PLAYER_OFFSET_X	(0.0f)
#define PLAYER_OFFSET_Y	(0.20f)
#define PLAYER_OFFSET_Z	(-10.0f)
#define CAMERA_OFFSET	(2.5f)
//プレイヤーの当たり判定の大きさ
#define PLAYER_SIZE_X	(0.05f)
#define PLAYER_SIZE_Y	(0.20f)
#define PLAYER_SIZE_Z	(0.05f)

//攻撃系
#define ATK_RAND_MAX	(1000)
#define ATK_RAND_MUL	(0.0001)


static int g_cameraIndex;
static int g_objIndex;
static int g_colIndex;
static int g_hitColIndex;

static int g_HP;			// PLAYERの体力
static float g_isAiming;


void InitPlayer(void) {
	g_objIndex = SetGameObject();
	g_cameraIndex = GetCameraIndex();
	SetGameObjectParent(g_cameraIndex, g_objIndex);

	g_colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);


	g_hitColIndex = SetCollision(LAYER_PLAYER, TYPE_BC);
	int index = GetColObjectIndex(g_hitColIndex);
	SetScale(index, XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
	SetPosition(index, GetPosition(g_objIndex));


	g_HP = 10;
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
			if (GetInputPress(MOVE_DASH) && !g_isAiming) {
				vec = MulXMFLOAT3(vec, SetXMFLOAT3(MOVE_POWER + DASH_POWER));
			}
			else {
				if (g_isAiming) {
					vec = MulXMFLOAT3(vec, SetXMFLOAT3(MOVE_POWER/4.0f));
				}
				else {
					vec = MulXMFLOAT3(vec, SetXMFLOAT3(MOVE_POWER));
				}
				
			}

			pos = AddXMFLOAT3(pos, vec);
			SetPosition(g_objIndex, pos);
		}




		DllRotation(GetLookInput(0), &rot, 0.03f);

		//カメラが縦方向に一回転しないように制限する
		rot.z = Clamp(rot.z, -XM_PI / 2.0f, XM_PI / 2.0f);

		SetRotation(g_objIndex, rot);
	}

	//カメラの更新
	SetGameObjectZERO(g_cameraIndex);	//親からみた情報を０にする
	SetPosition(g_cameraIndex, XMFLOAT3(0.0f, CAMERA_OFFSET, 0.0f));	//親からみた座標を少し高くする


	//当たり判定
	{
		//攻撃に対する当たり判定の更新
		SetPosition(GetColObjectIndex(g_hitColIndex), pos);
		if (GetColAns(g_hitColIndex)) {
			g_HP--;		//攻撃の種類にかぎらず１ダメージ（強い攻撃は重ねればどうにかなる）
		}

		if (g_HP <= 0) {
			SetIsClear(false);
			SetMode(MODE_RESULT);
		}


		//移動に対する当たり判定の更新
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





	//攻撃処理
	{
		//覗く
		if (GetInputPress(AIMING)) {
			UI_ELEMENT* ui = GetUI(ATK_MAHOUZIN);
			ui->use = true;
			g_isAiming = true;
			if (GetInputPress(ATK_1)) {
				int index = SetGameObject();
				pos.y += CAMERA_OFFSET;

				//発射位置を自分より少し前に移動する
				XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);
				vec.x += sinf(rot.x);
				vec.z += cosf(rot.x);
				vec.y -= tanf(rot.z);
				vec = NormalizeXMFLOAT3(vec);
				pos = AddXMFLOAT3(pos, vec);
				SetPosition(index, pos);

				SetRotation(index, rot);
				SetScale(index, scl);
				//攻撃力を調整するために二回Setする
				SetAttack(ATK_PLAYER_1, index);
				//SetAttack(ATK_PLAYER_1, index);
				DelGameObject(index);
			}
		}
		//腰撃ち
		else {
			UI_ELEMENT* ui = GetUI(ATK_MAHOUZIN);
			ui->use = false;
			g_isAiming = false;
			if (GetInputPress(ATK_1)) {
				int index = SetGameObject();
				pos.y += CAMERA_OFFSET;

				//発射位置を自分より少し前に移動する
				XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);
				vec.x += sinf(rot.x);
				vec.z += cosf(rot.x);
				vec.y -= tanf(rot.z);
				vec = NormalizeXMFLOAT3(vec);
				pos = AddXMFLOAT3(pos, vec);
				SetPosition(index, pos);

				//弾道のブレを発生させる
				XMFLOAT3 tempRot = XMFLOAT3((rand() % ATK_RAND_MAX), (rand() % ATK_RAND_MAX), (rand() % ATK_RAND_MAX));
				tempRot = SubXMFLOAT3(tempRot, SetXMFLOAT3(ATK_RAND_MAX / 2));
				tempRot = MulXMFLOAT3(tempRot, SetXMFLOAT3(ATK_RAND_MUL));
				tempRot = AddXMFLOAT3(rot, tempRot);
				SetRotation(index, tempRot);

				//一応スケールも更新しておく
				SetScale(index, scl);
				SetAttack(ATK_PLAYER_1, index);
				DelGameObject(index);
			}
		}
		if (GetInputPress(ATK_2)) {
			SetAttack(ATK_PLAYER_2, g_cameraIndex);
		}
	}


	//シーン遷移
	if (g_HP <= 0) SetMode(MODE_RESULT);

}
void DrawPlayer(void) {

}


int GetPlayerGameObjectIndex(void) {
	return g_objIndex;
}
int GetPlayerColObjectIndex(void) {
	return g_colIndex;
}
int GetPlayerHitColObjectIndex(void) {
	return g_hitColIndex;
}