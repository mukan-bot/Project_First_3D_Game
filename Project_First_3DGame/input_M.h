//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

HRESULT InitMinput(HWND hWnd);
void UpdateMinput(void);

//マウスの移動量
XMFLOAT2 GetMouseVec(void);
//マウスの座標
XMFLOAT2 GetMousePos(void);	

void SetCursorMove(bool is);//trueなら動く