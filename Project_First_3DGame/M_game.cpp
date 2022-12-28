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



HRESULT InitGame(void) {
	
	InitGameModel();

	InitCameraM_Game();

	InitField();


	InitPlayer();

	InitUI();

	InitAttack();
	
	SetCursorMove(false);

	

	return S_OK;
}
void UninitGame(void) {

	UninitField();

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

	XMFLOAT3 pos1 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 pos2 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 pos3 = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 pos4 = XMFLOAT3(0.0f, 2.0f, 0.0f);



}


void DrawGame(void) {
	DrawPlayer();
	
	DrawAttack();
	
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