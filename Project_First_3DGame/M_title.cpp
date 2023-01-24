#include "M_title.h"
#include "title_bg.h"
#include "title_ui.h"





HRESULT InitTitle(void) {

	InitTitleBG();
	InitTitleUI();
	return S_OK;
}

void UninitTitle(void) {
	UninitTitleBG();
	UninitTitleUI();
}

void UpdateTitle(void) {
	UpdateTitleBG();
	UpdateTitleUI();
}

void DrawTitle(void) {

	DrawTitleBG();

	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);


	
	DrawTitleUI();


	// ���C�e�B���O��L����
	SetLightEnable(false);
	// Z��r����
	SetDepthEnable(true);
}