#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"
#include "title_fog.h"

#include "title_field.h"
#include "title_anime.h"

#include "camera.h"


HRESULT InitTitle(void) {
	InitGameObject();
	InitGameModel();

	InitTitleAinme();
	InitTitleField();

	InitCameraM_Game();
	int index = GetCameraIndex();
	SetPosition(index, XMFLOAT3(-35.0f, 10.0f, 0.0f));
	SetRotation(index, XMFLOAT3(-XM_PI / 2, 0.0f, 0.4f));


	InitTitleBG();

	InitTitleFOG();

	InitTitleUI();

	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();

	UninitTitleFOG();

	UninitTitleUI();

	UninitTitleAnime();
	UninitTitleField();

	UninitGameModel();
}

void UpdateTitle(void) {
	UpdateTitleBG();
	
	UpdateTitleFOG();

	UpdateTitleUI();

	UpdateTitleAnime();
	UpdateTitleField();

	UpdateGameObject();
}

void DrawTitle(void) {

	// ライティングを無効
	SetLightEnable(false);

	DrawGameModel();

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);

	//DrawTitleBG();


	DrawTitleUI();


	DrawTitleFOG();


	// ライティングを有効に
	SetLightEnable(true);
	// Z比較あり
	SetDepthEnable(true);
}