#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"
#include "title_fog.h"




HRESULT InitTitle(void) {

	InitTitleBG();

	InitTitleFOG();

	InitTitleUI();

	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();

	UninitTitleFOG();

	UninitTitleUI();
}

void UpdateTitle(void) {
	UpdateTitleBG();
	
	UpdateTitleFOG();

	UpdateTitleUI();
}

void DrawTitle(void) {
	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);
	// ライティングを無効
	SetLightEnable(false);


	DrawTitleBG();


	DrawTitleUI();


	DrawTitleFOG();


	// ライティングを有効に
	SetLightEnable(true);
	// Z比較あり
	SetDepthEnable(true);
}