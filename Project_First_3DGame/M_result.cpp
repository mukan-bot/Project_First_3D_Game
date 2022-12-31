//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "M_result.h"

#include "result_bg.h"



HRESULT InitResult(void) {
	InitResultBG();

	return S_OK;
}
void UninitResult(void) {
	UninitResultBG();
}
void UpdateResult(void) {
	UpdateResultBG();
}
void DrawResult(void) {
	// 2D�̕���`�悷�鏈��
// Z��r�Ȃ�
	SetDepthEnable(false);
	// ���C�e�B���O�𖳌�
	SetLightEnable(false);


	DrawResultBG();


	// ���C�e�B���O��L����
	SetLightEnable(false);	//TODO:���C�g�������true�ɕς���
	// Z��r����
	SetDepthEnable(true);
}

