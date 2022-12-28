//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

using namespace DirectX;


void UpdateGameObject(void);	//GameObject�̍X�V�iUpdate�̈�ԉ��ɒu���j

int SetGameObject(void);		//GameObject���g���i�߂�n�̓C���f�b�N�X�ԍ��j
void DelGameObject(int index);	//GameObject��j������i�������̎g�p�ʂ͕ς��Ȃ��j


//�Z�b�g�E�Q�b�g�֐��iindex��SetGameObject�̖߂�l�j

void SetPosition(int index, XMFLOAT3 position);
void SetRotation(int index, XMFLOAT3 rotation);
void SetScale(int index, XMFLOAT3 scale);
void SetGameObjectParent(int index, int parentIndex); 
void SetGameObjectZERO(int index);			//�S�Ă̒l��0�ɂ���

XMFLOAT3 GetPosition(int index);
XMFLOAT3 GetRotation(int index);
XMFLOAT3 GetScale(int index);
int GetGameObjectParent(int index);