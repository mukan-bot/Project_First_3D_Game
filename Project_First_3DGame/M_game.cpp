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
}


void DrawGame(void) {

	DrawPlayer();
	DrawAttack();
	
	DrawField();


	

	// 2D�̕���`�悷�鏈��
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	

	// Z��r�Ȃ�
	SetDepthEnable(false);


	DrawEnemy();

	DrawParticle();

	DrawUI();


	// ���C�e�B���O��L����
	SetLightEnable(true);
	// Z��r����
	SetDepthEnable(true);
}