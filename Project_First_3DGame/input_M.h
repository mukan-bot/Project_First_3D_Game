//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

HRESULT InitMinput(HWND hWnd);
void UpdateMinput(void);


XMFLOAT2 GetMouseVec(void);	//�}�E�X�̈ړ���
XMFLOAT2 GetMousePos(void);	//�}�E�X�̍��W

void SetCursorMove(bool is);//true�Ȃ瓮��