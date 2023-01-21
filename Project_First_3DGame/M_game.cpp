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
#include "EnemyHP.h"


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

	InitEnemyHpBar();

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

	UninitEnemyHpBar();

}
void UpdateGame(void) {


	UpdateCollision();
	UpdatePlayer();
	UpdateEnemy();


	UpdateAttack();

	UpdateUI();
	UpdateParticle();

	UpdateField();

	UpdateEnemyHpBar();
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

	DrawEnemy();

	DrawParticle();

	DrawUI();

	DrawEnemyHpBar();

	// ライティングを有効に
	SetLightEnable(true);
	// Z比較あり
	SetDepthEnable(true);
}