//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGameModel(void);
void UninitGameModel(void);
void DrawGameModel(void);
//���f�����Z�b�g����
int SetGameModel(char* modelPath, int gameObjectIndex, int fuchi, CULL_MODE cullMode);
//���f�����폜����
void DelGameModel(int index);
//���f���̃X�P�[�����Z�b�g����iGameObject��scale*�j
void SetGameModelScale(int index, XMFLOAT3 scale);
//���f���𒼐ڂ����肽�����p
DX11_MODEL* GetModel(int index);
//���C���[�t���[���ŕ\���ł���悤��
void SetGameModeFill(int index, D3D11_FILL_MODE model);
