//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

HRESULT InitMinput(HWND hWnd);
void UpdateMinput(void);

//�}�E�X�̈ړ���
XMFLOAT2 GetMouseVec(void);
//�}�E�X�̍��W
XMFLOAT2 GetMousePos(void);	

void SetCursorMove(bool is);//true�Ȃ瓮��