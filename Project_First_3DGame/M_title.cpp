#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"





HRESULT InitTitle(void) {

	InitTitleBG();
	InitTitleUI();
	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();
	UninitTitleUI();
}

void UpdateTitle(void) {
	UpdateTitleBG();
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


	// ライティングを有効に
	SetLightEnable(false);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}