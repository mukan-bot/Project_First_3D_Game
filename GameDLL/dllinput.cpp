#include "dllinput.h"

#define CONTROLLER_MAX	(4)	//�R���g���[���[�̍ő�ڑ����iXinput�̍ő傪�S�j
#define PAD(index)	state[index].Gamepad



struct GAMEPAD_STATUS {
	//�e��{�^����������Ă��邩
	//t���͉����ꂽ�u�Ԃ��ǂ����̔��f
	//r���͕����ꂽ�u�Ԃ��ǂ����̔��f
	bool A;
	bool tA;
	bool rA;
	bool B;
	bool tB;
	bool rB;
	bool X;
	bool tX;
	bool rX;
	bool Y;
	bool tY;
	bool rY;
	bool L;
	bool tL;
	bool rL;
	bool R;
	bool tR;
	bool rR;

	//�X�e�B�b�N�̍��W(int�Ƃ�short�ŗǂ����ǁA�Q�[�����ł悭�g���^�ɂ��Ă���)
	XMFLOAT2 sL;
	XMFLOAT2 sR;

	//�g���K�[�̒l
	int t
};



GAMEPAD_STATUS g_Gpad[3];	//�Q�[���p�b�h�̏��
bool g_use[3];				//�ڑ�����Ă��邩



void UpdateInput(void) {
	XINPUT_STATE state[CONTROLLER_MAX];	//�R���g���[���[�̏�

	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(index, &state[index]);
		if (dwResult == ERROR_SUCCESS){	//�ڑ�����
			g_use[index] = true;
			if (PAD(index).wButtons = XINPUT_GAMEPAD_A) {
				g_Gpad[index].tA = !g_Gpad[index].A;	//A��false�ł����ɗ�����Ă��Ƃ́A�����ꂽ�u��
			}
		}
		else{							//�ڑ����s
			g_use[index] = false;
		}
	}
}

DLLEXPOERT bool GetXinputPressA(void) {
	return false;	//TODO:�Q�[���p�b�h�̓��͂̂������@���l����
}