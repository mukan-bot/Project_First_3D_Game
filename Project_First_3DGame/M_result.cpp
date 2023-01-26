//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_result.h"

#include "result_bg.h"
#include "result_ui.h"



HRESULT InitResult(void) {
	InitResultBG();
	InitResultUI();
	return S_OK;
}
void UninitResult(void) {
	UninitResultBG();
	UninitResultUI();
}
void UpdateResult(void) {
	UpdateResultBG();
	UpdateResultUI();
}
void DrawResult(void) {
	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	DrawResultBG();
	DrawResultUI();

	// ���C�e�B���O��L����
	SetLightEnable(true);	//TODO:���C�g�������true�ɕς���
	// Z��r����
	SetDepthEnable(true);
}

