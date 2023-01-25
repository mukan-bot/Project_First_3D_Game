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
}
void DrawTitleBG(void) {
}