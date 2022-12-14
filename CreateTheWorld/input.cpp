//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "input.h"
#include "input_D.h"
#include "input_X.h"


int KeyName[BUTTON_MAX];
DWORD DinputName[BUTTON_MAX];
DWORD XinputName[BUTTON_MAX];

float g_XlookSensitive = 30000.0f;


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
	bool ans = false;	//戻り地はintだけどboolで管理する。戻り地がintなのは計算で使いやすくするため
	if (GetKeyboardPress(KeyName[button])) ans = true;
	if (IsButtonPressed(padNo, DinputName[button])) ans = true;
	XINPUT_STATE state = GetXinput(padNo);
	if (state.Gamepad.wButtons & XinputName[button]) ans = true;
	return (int)ans;
}

int GetInputTrigger(ButtonName button, int padNo) {
	bool ans = false;
	if (GetKeyboardTrigger(KeyName[button])) ans = true;
	if (IsButtonTriggered(padNo, DinputName[button])) ans = true;
	XINPUT_STATE state = GetXinputTrigger(padNo);
	if (state.Gamepad.wButtons & XinputName[button]) ans = true;
	return (int)ans;
}

int GetInputRelease(ButtonName button, int padNo) {
	bool ans = false;
	if (GetKeyboardRelease(KeyName[button])) ans = true;

	XINPUT_STATE state = GetXinputRelease(padNo);
	if (state.Gamepad.wButtons & XinputName[button]) ans = true;

	return (int)ans;
}


XMFLOAT2 GetLookInput(int padNo) {
	XMFLOAT2 ans = XMFLOAT2(0.0f, 0.0f);
	
	if (ans.x == 0 && ans.y == 0) {
		if (GetKeyboardPress(DIK_UP)) ans.y--;
		if (GetKeyboardPress(DIK_DOWN)) ans.y++;
		if (GetKeyboardPress(DIK_RIGHT)) ans.x++;
		if (GetKeyboardPress(DIK_LEFT)) ans.x--;
	}

	if (ans.x == 0 && ans.y == 0) {
		//DirectInputのやつ書く
	}


	if (ans.x == 0 && ans.y == 0) {
		XINPUT_STATE state = GetXinputTrigger(padNo);


		// デッドゾーン以下を0にする
		if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}
		else {
			ans.x = state.Gamepad.sThumbRX / g_XlookSensitive;

			ans.y = -state.Gamepad.sThumbRY / g_XlookSensitive;
		}

	}

	return ans;
}

void SetXinputSensitive(float sensitive) {
	g_XlookSensitive = sensitive;
}
float GetXinputSensitive(void) {
	return g_XlookSensitive;
}