//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"

void InitCameraM_Game(void);	
void UpdateCamera(void);
void DrawCamera(void);

//カメラのGameObjectのインデックスを参照する
int GetCameraIndex(void);
//カメラのマトリックスを参照
XMFLOAT4X4 GetCameraMtxView(void);