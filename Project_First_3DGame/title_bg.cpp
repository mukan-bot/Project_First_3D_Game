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


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_MODEL_MAX		(20)
#define TITLE_MODEL_MAIN	("./data/MODEL/Skull/skull.obj")
#define TITLE_MODEL_PARTS	("./data/MODEL/Skull/jaw.obj")

#define TITLE_MOVE_COUNT	(440)
#define TITLE_OFFSET_POS	(XMFLOAT3(0.0f, 10.0f, 10.0f))
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int objIndex[TITLE_MODEL_MAX];			//メイン用
static int modelIndex[TITLE_MODEL_MAX];
static int partsObjIndex[TITLE_MODEL_MAX];
static int modelPartsIndex[TITLE_MODEL_MAX];
static int count[TITLE_MODEL_MAX];

HRESULT InitTitleBG(void) {
	InitGameObject();
	InitGameModel();

	for (int i = 0; i < TITLE_MODEL_MAX; i++) {
		objIndex[i] = SetGameObject();
		SetScale(objIndex[i], SetXMFLOAT3(0.005f));
		modelIndex[i] = SetGameModel(TITLE_MODEL_MAIN, objIndex[i], 0, CULL_MODE_BACK);
		SetGameModelDissolve(modelIndex[i],1.0f);


		partsObjIndex[i] = SetGameObject();
		SetGameObjectParent(partsObjIndex[i], objIndex[i]);
		modelPartsIndex[i] = SetGameModel(TITLE_MODEL_PARTS, partsObjIndex[i], 0, CULL_MODE_BACK);
		SetGameModelDissolve(modelPartsIndex[i], 1.0f);

		// 初期座標のセット
		//SetPosition(objIndex[i], TITLE_OFFSET_POS);
		// 出現のタイミングをバラつかせる
		count[i] = rand() % TITLE_MOVE_COUNT;
	}


	return S_OK;
}
void UninitTitleBG(void) {
	UninitGameModel();
}
void UpdateTitleBG(void) {

}
void DrawTitleBG(void) {
	DrawGameModel();
}