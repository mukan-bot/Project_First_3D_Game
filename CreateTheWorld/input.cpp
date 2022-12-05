#include "main.h"
#include "input.h"
#include "input_D.h"
#include "input_X.h"

int KeyName[BUTTON_MAX];
DWORD DinputName[BUTTON_MAX];
DWORD XinputName[BUTTON_MAX];

HRESULT InitInput(HINSTANCE hInst, HWND hWnd) {
	InitDinput(hInst, hWnd);

	//ボタンの名前を整える
	//TODO:ボタン配置はプレイしやすいように調整する
	for (int i = 0; i < BUTTON_MAX; i++){
		ButtonName name = (ButtonName)i;
		switch (name)
		{
		case MOVE_FRONT:
			KeyName[i] = DIK_W;
			DinputName[i] = BUTTON_UP;
			XinputName[i] = XINPUT_GAMEPAD_DPAD_UP;
			break;
		case MOVE_BACK:
			KeyName[i] = DIK_S;
			DinputName[i] = BUTTON_DOWN;
			XinputName[i] = XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case MOVE_LEFT:
			KeyName[i] = DIK_A;
			DinputName[i] = BUTTON_LEFT;
			XinputName[i] = XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case MOVE_RIGHT:
			KeyName[i] = DIK_D;
			DinputName[i] = BUTTON_RIGHT;
			XinputName[i] = XINPUT_GAMEPAD_DPAD_RIGHT;
			break;
		case MOVE_JUMP:
			KeyName[i] = DIK_SPACE;
			DinputName[i] = BUTTON_X;
			XinputName[i] = XINPUT_GAMEPAD_A;
			break;
		case MOVE_DASH:
			KeyName[i] = DIK_LSHIFT;
			DinputName[i] = BUTTON_L;
			XinputName[i] = XINPUT_GAMEPAD_LEFT_THUMB;
			break;
		case ATK_1:
			KeyName[i] = DIK_1;
			DinputName[i] = BUTTON_A;
			XinputName[i] = XINPUT_GAMEPAD_B;
			break;
		case ATK_2:
			KeyName[i] = DIK_2;
			DinputName[i] = BUTTON_B;
			XinputName[i] = XINPUT_GAMEPAD_Y;
			break;
		default:
			break;
		}
	}

	return S_OK;

}
void UninitInput(void) {
	UninitDinput();
}
void UpdateInput(void) {
	UpdateDinput();
	UpdateXinput();
}

int GetInputPress(ButtonName button, int padNo) {
	bool ans = false;
	if (GetKeyboardPress(KeyName[button])) ans = true;
	if (IsButtonPressed(padNo, DinputName[button])) ans = true;
	XINPUT_STATE state = GetXinput(padNo);
	if (state.Gamepad.wButtons & XinputName[button]) ans = true;
	return ans;
}

int GetCinputPress(cButtonName button, int padNo) {
	int ans = 0;
	return ans;
}

bool GetInputTrigger(ButtonName button, int padNo) {
	bool ans = false;
	return ans;
}
int GetCinputTrigger(cButtonName button, int padNo) {
	int ans = 0;
	return ans;
}

bool GetInputRelease(ButtonName button, int padNo) {
	bool ans = false;
	return ans;
}

int GetCinputRelease(cButtonName button, int padNo) {
	int ans = 0;
	return ans;
}