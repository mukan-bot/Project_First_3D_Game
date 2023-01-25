//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "title_bg.h"
#include "GameObject.h"
#include "GameModel.h"
#include "camera.h"

#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_MODEL_MAX		(20)
#define TITLE_MODEL_MAIN	("./data/MODEL/Skull/skull.obj")
#define TITLE_MODEL_PARTS	("./data/MODEL/Skull/jaw.obj")

#define TITLE_MOVE_COUNT	(240)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int objIndex[TITLE_MODEL_MAX];			//メイン用
static int modelIndex[TITLE_MODEL_MAX];
static int partsObjIndex[TITLE_MODEL_MAX];
static int modelPartsIndex[TITLE_MODEL_MAX];
static int count[TITLE_MODEL_MAX];

HRESULT InitTitleBG(void) {

	return S_OK;
}
void UninitTitleBG(void) {
}
void UpdateTitleBG(void) {

	for (int i = 0; i < TITLE_MODEL_MAX; i++) {
		if (count[i] < 0) {
			if (count[i] < -TITLE_MOVE_COUNT) {
				count[i] = 0;

				// 初期座標のセット
				SetPosition(objIndex[i], XMFLOAT3(0.0f, 0.0f, 3.0f));
				SetRotation(objIndex[i], XMFLOAT3((rand() % 628) / 100, (rand() % 628) / 100, (rand() % 628) / 100));
			}
			else {
				XMFLOAT3 vec;
				XMFLOAT3 pos, rot;
				pos = GetPosition(objIndex[i]);
				rot = GetRotation(objIndex[i]);

				vec.x = sinf(rot.x);
				vec.z = cosf(rot.x);
				vec.y = tanf(rot.z);

				vec = NormalizeXMFLOAT3(vec);

				vec = MulXMFLOAT3(vec, SetXMFLOAT3(0.01f));

				pos = AddXMFLOAT3(pos, vec);
				SetPosition(objIndex[i], pos);

				count[i]--;
			}
		}
		else {
			count[i]--;
		}
	}


	UpdateGameObject();
}
void DrawTitleBG(void) {
}