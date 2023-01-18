//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_MAX	(20)



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

// �G�l�~�[�̔z�u
void SetEnemy(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);
// ���̂�ENEMY�������Ă邩
int GetAliveEnemy(void);
// �G�l�~�[��GameObjectIndex�̏����i�g�p����Ă��Ȃ��C���f�N�X���w�肳�ꂽ�ꍇ-1��Ԃ��j
int GetEnemyIndex(int index);
// �G�l�~�[��HP������
int GetEnemyHP(int index);
// �G�l�~�[��HP���Z�b�g
void SetEnemyHP(int index, int hp);