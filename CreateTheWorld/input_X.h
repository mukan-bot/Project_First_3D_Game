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

XINPUT_STATE GetXinput(int index);
XINPUT_STATE GetXinputTrigger(int index); 
XINPUT_STATE GetXinputRelease(int index);