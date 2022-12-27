//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"

#include "input_M.h"
#include "collision.h"
#include "field.h"
#include "player.h"
#include "UI.h"



HRESULT InitGame(void) {
	
	InitGameModel();

	InitField();


	InitPlayer();

	InitUI();
	
	SetCursorMove(false);

	

	return S_OK;
}
void UninitGame(void) {

	UninitField();

	UninitPlayer();

	UninitUI();

	UninitGameModel();


}
void UpdateGame(void) {
	UpdatePlayer();
	UpdateCollision();
	UpdateUI();
}


void DrawGame(void) {
	DrawPlayer();
	
	
	DrawField();

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);
	// ライティングを無効
	SetLightEnable(false);


	DrawUI();


	// ライティングを有効に
	SetLightEnable(false);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}