#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"
#include "title_field.h"
#include "title_anime.h"

#include "camera.h"

#include "input.h"



HRESULT InitTitle(void) {

	InitGameObject();
	InitGameModel();


	InitTitleBG();
	InitTitleUI();
	InitTitleAinme();
	InitTitleField();

	InitCameraM_Game();
	int index = GetCameraIndex();
	SetPosition(index, XMFLOAT3(-35.0f, 10.0f, 0.0f));
	SetRotation(index, XMFLOAT3(-XM_PI/2, 0.0f, 0.4f));

	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();
	UninitTitleUI();
	UninitTitleAnime();
	UninitTitleField();

	UninitGameModel();
}

void UpdateTitle(void) {
	UpdateTitleBG();
	UpdateTitleUI();
	UpdateTitleAnime();
	UpdateTitleField();

	UpdateGameObject();
}

void DrawTitle(void) {

	DrawTitleBG();
	DrawTitleAnime();


	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	DrawGameModel();

	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);

	
	DrawTitleUI();


	// ���C�e�B���O��L����
	SetLightEnable(false);
	// Z��r����
	SetDepthEnable(true);
}