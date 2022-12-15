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

//Xinput�R���g���[���[�̓��͂̏����i���̏�ԁj
//Index�ɃR���g���[���[�̍ő�ڑ����ȏ�̒l������Ɨ�O���o���B
XINPUT_STATE GetXinput(int index);
//Xinput�R���g���[���[�̓��͂̏����i�����ꂽ�u�Ԃ��j
//Index�ɃR���g���[���[�̍ő�ڑ����ȏ�̒l������Ɨ�O���o���B
XINPUT_STATE GetXinputTrigger(int index);
//Xinput�R���g���[���[�̓��͂̏����i�b���ꂽ�u�Ԃ��j
//Index�ɃR���g���[���[�̍ő�ڑ����ȏ�̒l������Ɨ�O���o���B
XINPUT_STATE GetXinputRelease(int index);