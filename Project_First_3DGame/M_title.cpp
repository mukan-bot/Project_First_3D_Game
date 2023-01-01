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
	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);


	DrawTitleBG();
	DrawTitleUI();


	// ���C�e�B���O��L����
	SetLightEnable(false);	//TODO:���C�g�������true�ɕς���
	// Z��r����
	SetDepthEnable(true);
}