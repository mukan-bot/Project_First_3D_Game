//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "input.h"
#include "input_D.h"
#include "input_X.h"
#include "input_M.h"

int KeyName[BUTTON_MAX];
DWORD DinputName[BUTTON_MAX];
DWORD XinputName[BUTTON_MAX];

float g_XlookSensitive = 0.00003f;
float g_MlookSensitive = 0.01f;

SELECT_CONTROLLER g_selectController = KEYBOARD;


HRESULT InitInput(HINSTANCE hInst, HWND hWnd) {
	InitDinput(hInst, hWnd);
	InitMinput(hWnd);
	//�{�^���̖��O�𐮂���
	//TODO:�{�^���z�u�̓v���C���₷���悤�ɒ�������
	//TODO:�}�E�X����͗v����
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
	//��ʂ��A�N�e�B�u����Ȃ��Ȃ���͂��󂯕t���Ȃ�
	if (GetWindowActive()) {
		UpdateDinput();
		UpdateXinput();
		UpdateMinput();
	}
}

int GetInputPress(ButtonName button, int padNo) {
	bool ans = false;	//�߂�n��int������bool�ŊǗ�����B�߂�n��int�Ȃ̂͌v�Z�Ŏg���₷�����邽��

	if (GetWindowActive()) {	//�E�C���h�E���A�N�e�B�u����Ȃ��ꍇ����
		switch (g_selectController)
		{
		case KEYBOARD:
			if (GetKeyboardPress(KeyName[button])) ans = true;
			break;
		case XBOX:
			XINPUT_STATE state = GetXinput(padNo);
			if (state.Gamepad.wButtons & XinputName[button]) ans = true;
			break;
		case PS:
			if (IsButtonPressed(padNo, DinputName[button])) ans = true;
			break;
		default:
			break;
		}
		
		

	}
	return (int)ans;
}

//�g�pController�̌�����܂߂Ă�
int GetInputTrigger(ButtonName button, int padNo) {
	bool ans = false;	//�߂�n��int������bool�ŊǗ�����B�߂�n��int�Ȃ̂͌v�Z�Ŏg���₷�����邽��

	if (GetWindowActive()) {	//�E�C���h�E���A�N�e�B�u����Ȃ��ꍇ����

		if (GetKeyboardTrigger(KeyName[button])) {

			SetSelectController(KEYBOARD);
			ans = (int)true;
		}
		XINPUT_STATE state = GetXinputTrigger(padNo);
		if (state.Gamepad.wButtons & XinputName[button]) {
			SetSelectController(XBOX);
			ans = (int)true;
		}
		if (IsButtonTriggered(padNo, DinputName[button])) {
			SetSelectController(PS);
			ans = (int)true;
		}
	}
	return (int)ans;
}

int GetInputRelease(ButtonName button, int padNo) {
	bool ans = false;	//�߂�n��int������bool�ŊǗ�����B�߂�n��int�Ȃ̂͌v�Z�Ŏg���₷�����邽��
	if (GetWindowActive()) {	//�E�C���h�E���A�N�e�B�u����Ȃ��ꍇ����
		switch (g_selectController)
		{
		case KEYBOARD:
			if (GetKeyboardRelease(KeyName[button])) ans = true;
			break;
		case XBOX:
			XINPUT_STATE state = GetXinputRelease(padNo);
			if (state.Gamepad.wButtons & XinputName[button]) ans = true;
			break;
		case PS:
			GetInputTrigger(button, padNo);	//MEMO:Trigger�̕��@���킩���
			break;
		default:
			break;
		}
	}
	return (int)ans;
}


XMFLOAT2 GetLookInput(int padNo) {
	XMFLOAT2 ans = XMFLOAT2(0.0f, 0.0f);

	if (GetWindowActive()) {	//�E�C���h�E���A�N�e�B�u����Ȃ��ꍇ����
		if (ans.x == 0 && ans.y == 0) {
			if (GetKeyboardPress(DIK_UP)) ans.y--;
			if (GetKeyboardPress(DIK_DOWN)) ans.y++;
			if (GetKeyboardPress(DIK_RIGHT)) ans.x++;
			if (GetKeyboardPress(DIK_LEFT)) ans.x--;
		}

		if (ans.x == 0 && ans.y == 0) {
			ans = GetMouseVec();
			ans.x *= g_MlookSensitive;
			ans.y *= g_MlookSensitive;
		}

		if (ans.x == 0 && ans.y == 0) {
			XINPUT_STATE state = GetXinputTrigger(padNo);

			// �f�b�h�]�[���ȉ���0�ɂ���
			if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}
			else {
				ans.x = state.Gamepad.sThumbRX * g_XlookSensitive;

				ans.y = -state.Gamepad.sThumbRY * g_XlookSensitive;
			}
		}

		if (ans.x == 0 && ans.y == 0) {
			//TODO:Dinput�킩���
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

void SetSelectController(SELECT_CONTROLLER select) {
	g_selectController = select;
}
SELECT_CONTROLLER GetSelectController(void) {
	return g_selectController;
}