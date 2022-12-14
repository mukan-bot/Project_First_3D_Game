//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

#include "main.h"
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define CONTROLLER_MAX	(4)	//コントローラーの最大接続数（Xinputの最大が４）


void UpdateXinput(void);

//Xinputコントローラーの入力の所得（今の状態）
//Indexにコントローラーの最大接続数以上の値を入れると例外を出す。
XINPUT_STATE GetXinput(int index);
//Xinputコントローラーの入力の所得（押された瞬間か）
//Indexにコントローラーの最大接続数以上の値を入れると例外を出す。
XINPUT_STATE GetXinputTrigger(int index);
//Xinputコントローラーの入力の所得（話された瞬間か）
//Indexにコントローラーの最大接続数以上の値を入れると例外を出す。
XINPUT_STATE GetXinputRelease(int index);