//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"

void InitCameraM_Game(void);	
void UpdateCamera(void);
void DrawCamera(void);

//�J������GameObject�̃C���f�b�N�X���Q�Ƃ���
int GetCameraIndex(void);
//�J�����̃}�g���b�N�X���Q��
XMFLOAT4X4 GetCameraMtxView(void);