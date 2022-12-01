#include "dllinput.h"

#define CONTROLLER_MAX	(4)	//コントローラーの最大接続数（Xinputの最大が４）
#define PAD(index)	state[index].Gamepad



struct GAMEPAD_STATUS {
	//各種ボタンが押されているか
	//t○は押された瞬間かどうかの判断
	//r○は放された瞬間かどうかの判断
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

	//スティックの座標(intとかshortで良いけど、ゲーム側でよく使う型にしておく)
	XMFLOAT2 sL;
	XMFLOAT2 sR;

	//トリガーの値
	int t
};



GAMEPAD_STATUS g_Gpad[3];	//ゲームパッドの情報
bool g_use[3];				//接続されているか



void UpdateInput(void) {
	XINPUT_STATE state[CONTROLLER_MAX];	//コントローラーの状況

	for (int index = 0; index < CONTROLLER_MAX; index++) {
		DWORD dwResult = XInputGetState(index, &state[index]);
		if (dwResult == ERROR_SUCCESS){	//接続成功
			g_use[index] = true;
			if (PAD(index).wButtons = XINPUT_GAMEPAD_A) {
				g_Gpad[index].tA = !g_Gpad[index].A;	//Aがfalseでここに来るってことは、押された瞬間
			}
		}
		else{							//接続失敗
			g_use[index] = false;
		}
	}
}

DLLEXPOERT bool GetXinputPressA(void) {
	return false;	//TODO:ゲームパッドの入力のいい方法を考える
}