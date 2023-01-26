//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_result.h"

#include "result_bg.h"
#include "result_ui.h"



HRESULT InitResult(void) {
	InitResultBG();
	InitResultUI();
	return S_OK;
}
void UninitResult(void) {
	UninitResultBG();
	UninitResultUI();
}
void UpdateResult(void) {
	UpdateResultBG();
	UpdateResultUI();
}
void DrawResult(void) {
	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);
	// ライティングを無効
	SetLightEnable(false);

	DrawResultBG();
	DrawResultUI();

	// ライティングを有効に
	SetLightEnable(true);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}

