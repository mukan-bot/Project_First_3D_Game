//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"

#include "input_X.h"


#define PAD(index)	state[index].Gamepad


bool g_use[CONTROLLER_MAX];				//�ڑ�����Ă��邩
XINPUT_STATE g_state[CONTROLLER_MAX];	//�R���g���[���[�̏�
XINPUT_STATE g_bstate[CONTROLLER_MAX];	//�R���g���[���[��1F�O�̏��


void UpdateXinput(void) {
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		g_bstate[index] = g_state[index];
	}
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(index, &g_state[index]);
		if (dwResult == ERROR_SUCCESS) {	//�ڑ�����
			g_use[index] = true;
		}
		else {							//�ڑ����s
			g_use[index] = false;
		}
	}
}

XINPUT_STATE GetXinput(int index) {
	if (index < CONTROLLER_MAX)return g_state[index];
}

XINPUT_STATE GetXinputTrigger(int index) {
	XINPUT_STATE ans = g_state[index];
	
	//�r���I�_���a�������1F�O��葝���Ă��镨�����
	ans.Gamepad.wButtons ^= g_bstate[index].Gamepad.wButtons;
	//AND������ĉ����ꂽ�L�[�̂ݏ�������
	ans.Gamepad.wButtons &= g_state[index].Gamepad.wButtons;

	

	return ans;
}

XINPUT_STATE GetXinputRelease(int index) {
	XINPUT_STATE ans = g_state[index];

	//�r���I�_���a�������1F�O��葝���Ă��镨�����
	ans.Gamepad.wButtons ^= g_bstate[index].Gamepad.wButtons;
	//AND������ĉ����ꂽ�L�[�̂ݏ�������
	ans.Gamepad.wButtons &= ~g_state[index].Gamepad.wButtons;

	
	return ans;
}