//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#pragma once

//*********************************************************
// �}�N����`
//*********************************************************

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


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//�ꉞint���߂�l�����ǁA�l��1or0������Abool�Ƃ��Ă�������͂��B

//�{�^����������Ă��邩
int GetInputPress(ButtonName button, int padN = 0);	
//�{�^���������ꂽ�u�Ԃ�
int GetInputTrigger(ButtonName button, int padNo = 0);	
//�{�^���������ꂽ�u�Ԃ�
int GetInputRelease(ButtonName button, int padNo = 0);	
//���_�̈ړ��Ɏg���i�₶�邵�L�[�̓��͂͊��x�ݒ�ł��Ȃ��j
XMFLOAT2 GetLookInput(int padNo);
//�������x��ύX
void SetInputSensitive(float sensitive);
//�������x���Q��
float GetInputSensitive(void);
//�ǂ̓��͑��u���g���Ă��邩�����߂�
void SetSelectController(SELECT_CONTROLLER select);
//���g���Ă�����͑��u���ǂꂩ���Q�Ƃ���
SELECT_CONTROLLER GetSelectController(void);