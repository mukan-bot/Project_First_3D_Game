//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"

#include "input_X.h"


#define PAD(index)	state[index].Gamepad


bool g_use[CONTROLLER_MAX];				//接続されているか
XINPUT_STATE g_state[CONTROLLER_MAX];	//コントローラーの状況
XINPUT_STATE g_bstate[CONTROLLER_MAX];	//コントローラーの1F前の状態


void UpdateXinput(void) {
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		g_bstate[index] = g_state[index];
	}
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(index, &g_state[index]);
		if (dwResult == ERROR_SUCCESS) {	//接続成功
			g_use[index] = true;
		}
		else {							//接続失敗
			g_use[index] = false;
		}
	}
}

XINPUT_STATE GetXinput(int index) {
	if (index < CONTROLLER_MAX)return g_state[index];
}

XINPUT_STATE GetXinputTrigger(int index) {
	XINPUT_STATE ans = g_state[index];
	
	//排他的論理和を取って1F前より増えている物を取る
	ans.Gamepad.wButtons ^= g_bstate[index].Gamepad.wButtons;
	//ANDを取って押されたキーのみ所得する
	ans.Gamepad.wButtons &= g_state[index].Gamepad.wButtons;

	

	return ans;
}

XINPUT_STATE GetXinputRelease(int index) {
	XINPUT_STATE ans = g_state[index];

	//排他的論理和を取って1F前より増えている物を取る
	ans.Gamepad.wButtons ^= g_bstate[index].Gamepad.wButtons;
	//ANDを取って押されたキーのみ所得する
	ans.Gamepad.wButtons &= ~g_state[index].Gamepad.wButtons;

	
	return ans;
}