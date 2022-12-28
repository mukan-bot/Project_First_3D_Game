//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

HRESULT InitMinput(HWND hWnd);
void UpdateMinput(void);


XMFLOAT2 GetMouseVec(void);	//マウスの移動量
XMFLOAT2 GetMousePos(void);	//マウスの座標

void SetCursorMove(bool is);//trueなら動く