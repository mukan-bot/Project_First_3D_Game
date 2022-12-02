#include "dllinput.h"
#include <Xinput.h>

#define CONTROLLER_MAX	(4)	//�R���g���[���[�̍ő�ڑ����iXinput�̍ő傪�S�j
#define PAD(index)	state[index].Gamepad


bool g_use[CONTROLLER_MAX];				//�ڑ�����Ă��邩
XINPUT_STATE g_state[CONTROLLER_MAX];	//�R���g���[���[�̏�


void UpdateInput(void) {
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(0, &g_state[index]);
		if (dwResult == ERROR_SUCCESS){	//�ڑ�����
			g_use[index] = true;
		}
		else{							//�ڑ����s
			g_use[index] = false;
		}
	}
}

DLLEXPOERT XINPUT_STATE GetXinput(int index) {
	return g_state[index];
}