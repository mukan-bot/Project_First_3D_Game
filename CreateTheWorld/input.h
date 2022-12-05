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
	
	BUTTON_MAX
};
enum cButtonName{
	//�R���g���[���[����
	MOVE_X,	//�W���C�X�e�B�b�N���g�p�����Ȃ߂炩�ȓ���X(�O��)
	MOVE_Y,	//�W���C�X�e�B�b�N���g�p�����Ȃ߂炩�ȓ���Y(���E)
	MOVE_T_DASH,	//�g���K�[�{�^�����g�p�����A�_�b�V���i���x���ׂ��������o����j
	
};



HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);


int GetInputPress(ButtonName button, int padN = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������
int GetCinputPress(cButtonName button, int padNo = 0);	//�R���g���[���[����̋@�\�̓���

bool GetInputTrigger(ButtonName button, int padNo = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������
int GetCinputTrigger(cButtonName button, int padNo = 0);	//�R���g���[���[����̋@�\�̓���

bool GetInputRelease(ButtonName button, int padNo = 0);	//�L�[�{�[�h�ƃR���g���[���[�œ�������
int GetCinputRelease(cButtonName button, int padNo = 0);	//�R���g���[���[����̋@�\�̓���