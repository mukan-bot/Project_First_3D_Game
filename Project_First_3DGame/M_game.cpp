//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_game.h"

#include "camera.h"
#include "input_M.h"
#include "collision.h"
#include "field.h"
#include "player.h"
#include "UI.h"
#include "attack.h"
#include "particle.h"



HRESULT InitGame(void) {
	
	InitGameModel();

	InitCameraM_Game();

	InitField();

	InitParticle();

	InitPlayer();

	InitUI();

	InitAttack();
	
	SetCursorMove(false);

	int index = SetCollision(LAYER_ENEMY, TYPE_BC);
	



	return S_OK;
}
void UninitGame(void) {

	UninitField();

	UninitParticle();

	UninitPlayer();

	UninitUI();

	UninitAttack();

	UninitGameModel();


}
void UpdateGame(void) {
	UpdatePlayer();
	UpdateCollision();
	UpdateAttack();
	UpdateUI();
	UpdateParticle();

	XMFLOAT3 pos1 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 pos2 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 pos3 = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 pos4 = XMFLOAT3(0.0f, 2.0f, 0.0f);



}


void DrawGame(void) {
	DrawPlayer();
	
	DrawAttack();
	
	DrawField();


	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);
	// ライティングを無効
	SetLightEnable(false);


	DrawParticle();

	DrawUI();


	// ライティングを有効に
	SetLightEnable(false);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}