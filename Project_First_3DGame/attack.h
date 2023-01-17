//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once
#include "main.h"

enum ATK_TYPE {	//MEMO:����͍U���͎l��ތŒ�
	ATK_PLAYER_1 = 0,
	ATK_PLAYER_2,
	ATK_ENEMY_1,
	ATK_ENEMY_2,

	ATK_TYPE_MAX,
};


struct ATTACK{
	bool use;				// �g���Ă��邩
	ATK_TYPE type;			// �ǂ̍U����
	int colIndex;			// �����蔻��
	int colObjIndex;		// �����蔻��̃I�u�W�F�N�g�C���f�b�N�X
	int fieldColIndex;		// �t�B�[���h�Ƃ̓����蔻��
	int fieldColObjIndex;	// �t�B�[���h�Ƃ̓����蔻��̃I�u�W�F�N�g�C���f�b�N�X
	int modelIndex;			// ���f����\�����鎞�p��gameModel�C���f�b�N�X

	int maxFlame;			// ���t���[���c�邩
	int countFlame;			// �����t���[���o������

	XMFLOAT3 vec;			//�ړ��̌����i���K������ĂȂ��Ă������j
};


HRESULT InitAttack(void);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);
// �U�����Z�b�g
void SetAttack(ATK_TYPE type, int objIndex);
