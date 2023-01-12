//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#pragma once



//����Q�[���쐬�Ŏg���{�^���ƃL�[��ݒ肷��
enum ButtonName {
	MOVE_FRONT,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_JUMP,
	MOVE_DASH,
	ATK_1,
	ATK_2,
	AIMING,
	BUTTON_MAX
};

enum SELECT_CONTROLLER {
	KEYBOARD,
	XBOX,
	PS,
};



HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//�ꉞint���߂�l�����ǁA�l��1or0������Abool�Ƃ��Ă�������͂��B
int GetInputPress(ButtonName button, int padN = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������
int GetInputTrigger(ButtonName button, int padNo = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������
int GetInputRelease(ButtonName button, int padNo = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������

XMFLOAT2 GetLookInput(int padNo);

void SetInputSensitive(float sensitive);	//Xinput�R���g���[���[�̎������x��ύX
float GetInputSensitive(void);				//Xinput�R���g���[���[�̎������x���Q��

void SetSelectController(SELECT_CONTROLLER select);
SELECT_CONTROLLER GetSelectController(void);