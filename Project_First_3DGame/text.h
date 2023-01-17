//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "sprite.h"


// �}�N����`

#define TEXT_MAX	(1280)	//�ő啶����

//�\���̒�`
struct TEXT {
	XMFLOAT2 pos;
	float size;
	XMFLOAT4 color;
};




// �v���g�^�C�v�錾
HRESULT Init_text(void);
void Uninit_text(void);
void Draw_text(void);
// �e�L�X�g���Z�b�g
void SetText(TEXT text_p, char text[]);
// �e�L�X�g���Z�b�g�i�����j
void SetText_d(TEXT text_p, int d);