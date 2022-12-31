//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_result.h"

#include "result_bg.h"



HRESULT InitResult(void) {
	InitResultBG();

	return S_OK;
}
void UninitResult(void) {
	UninitResultBG();
}
void UpdateResult(void) {
	UpdateResultBG();
}
void DrawResult(void) {
	// 2Dの物を描画する処理
// Z比較なし
	SetDepthEnable(false);
	// ライティングを無効
	SetLightEnable(false);


	DrawResultBG();


	// ライティングを有効に
	SetLightEnable(false);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}

