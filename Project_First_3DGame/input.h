//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#pragma once

//*********************************************************
// マクロ定義
//*********************************************************

//今回ゲーム作成で使うボタンとキーを設定する
enum ButtonName {
	MOVE_FRONT,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_JUMP,
	MOVE_DASH,
	ATK_1,
	ATK_2,
	AIMING,
	BUTTON_MAX
};

enum SELECT_CONTROLLER {
	KEYBOARD,
	XBOX,
	PS,
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//一応intが戻り値だけど、値は1or0だから、boolとしても扱えるはず。

//ボタンが押されているか
int GetInputPress(ButtonName button, int padN = 0);	
//ボタンが押された瞬間か
int GetInputTrigger(ButtonName button, int padNo = 0);	
//ボタンが放された瞬間か
int GetInputRelease(ButtonName button, int padNo = 0);	
//視点の移動に使う（やじるしキーの入力は感度設定できない）
XMFLOAT2 GetLookInput(int padNo);
//視線感度を変更
void SetInputSensitive(float sensitive);
//視線感度を参照
float GetInputSensitive(void);
//どの入力装置が使われているかを決める
void SetSelectController(SELECT_CONTROLLER select);
//今使われている入力装置がどれかを参照する
SELECT_CONTROLLER GetSelectController(void);