//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum COLLISION_TYPE
{
	TYPE_BB,	//�o�E���f�B���O�{�b�N�X
	TYPE_BC,	//�o�E���f�B���O�T�[�N��
};

enum COLLISION_LAYER 
{
	LAYER_PLAYER,		// �v���C���[�̑�
	LAYER_PLAYER_ATK,	// �v���C���[�̍U��
	LAYER_ENEMY,		// �G�l�~�[�̑�
	LAYER_ENEMY_ATK,	// �G�l�~�[�̍U��
	LAYER_OBSTACLE,		// �}�b�v�ɔz�u�����Q��
	LAYER_FIELD,
};

#define COLLISION_MAX (512)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct COLLISION
{
	bool use;				// �g���Ă��邩
	bool ans;				// �������Ă��邩��ۑ�
	int gameObjectIndex;	// �|�W�V�������Q�Ƃ���
	COLLISION_TYPE type;	// �����蔻��̃^�C�v��ۑ�
	COLLISION_LAYER layer;	// �����蔻��̃��[���[��ۑ�
#ifdef _DEBUG
	int gameModelIndex;		//�f�o�b�N�̂Ƃ��ɓ����蔻��\���ł���悤��
#endif // _DEBUG

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//collision�̃Z�b�g
int SetCollision(COLLISION_LAYER layer, COLLISION_TYPE type);
//collision�̍폜
void DelCollision(int index);
//collision�Ŏg�p���Ă���GameObject�̃C���f�b�N�X�̏���
int GetColObjectIndex(int index);
//collision�̓����蔻��̌��ʂ̏����i�ꏊ�ɂ���Ă͔��肪�����j
bool GetColAns(int index);
//���݂̓����蔻��̌��ʂ̏����i�d���Ȃ肪���j
bool GetColAnsUpdate(int index);

void InitCollision(void);
void UpdateCollision(void);
