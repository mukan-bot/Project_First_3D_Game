#include "dllinput.h"
#include <Xinput.h>

#define CONTROLLER_MAX	(4)	//コントローラーの最大接続数（Xinputの最大が４）
#define PAD(index)	state[index].Gamepad


bool g_use[CONTROLLER_MAX];				//接続されているか
XINPUT_STATE g_state[CONTROLLER_MAX];	//コントローラーの状況


void UpdateInput(void) {
	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(0, &g_state[index]);
		if (dwResult == ERROR_SUCCESS){	//接続成功
			g_use[index] = true;
		}
		else{							//接続失敗
			g_use[index] = false;
		}
	}
}

DLLEXPOERT XINPUT_STATE GetXinput(int index) {
	return g_state[index];
}