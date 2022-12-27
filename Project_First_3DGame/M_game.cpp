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

	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);


	DrawUI();


	// ���C�e�B���O��L����
	SetLightEnable(false);	//TODO:���C�g�������true�ɕς���
	// Z��r����
	SetDepthEnable(true);
}