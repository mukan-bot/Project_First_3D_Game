#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"
#include "title_fog.h"




HRESULT InitTitle(void) {

	InitTitleBG();

	InitTitleFOG();

	InitTitleUI();

	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();

	UninitTitleFOG();

	UninitTitleUI();
}

void UpdateTitle(void) {
	UpdateTitleBG();
	
	UpdateTitleFOG();

	UpdateTitleUI();
}

void DrawTitle(void) {
	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);


	DrawTitleBG();


	DrawTitleUI();


	DrawTitleFOG();


	// ���C�e�B���O��L����
	SetLightEnable(true);
	// Z��r����
	SetDepthEnable(true);
}