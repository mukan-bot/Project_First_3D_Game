//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

#include "main.h"
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define CONTROLLER_MAX	(4)	//�R���g���[���[�̍ő�ڑ����iXinput�̍ő傪�S�j


void UpdateXinput(void);

XINPUT_STATE GetXinput(int index);
XINPUT_STATE GetXinputTrigger(int index); 
XINPUT_STATE GetXinputRelease(int index);