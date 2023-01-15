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
#include "enemy.h"
#include "input.h"


HRESULT InitGame(void) {
	InitGameObject();

	InitGameModel();

	InitCollision();

	InitCameraM_Game();

	InitParticle();

	InitPlayer();

	InitEnemy();

	InitField();

	InitUI();

	InitAttack();

	return S_OK;
}
void UninitGame(void) {

	UninitField();

	UninitParticle();

	UninitPlayer();

	UninitEnemy();

	UninitUI();

	UninitAttack();

	UninitGameModel();


}
void UpdateGame(void) {


	UpdateCollision();
	UpdatePlayer();
	UpdateEnemy();


	UpdateAttack();

	UpdateUI();
	UpdateParticle();

	UpdateField();

	if (GetInputPress(MOVE_JUMP)) {
		SetPixelFill(D3D11_FILL_WIREFRAME);
	}
	else {
		SetPixelFill(D3D11_FILL_SOLID);
	}
}


void DrawGame(void) {

	DrawPlayer();
	DrawEnemy();
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
	SetLightEnable(true);	//TODO:ライト作ったらtrueに変える
	// Z比較あり
	SetDepthEnable(true);
}