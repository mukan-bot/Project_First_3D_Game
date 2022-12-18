//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

//�悭�g���v�Z�Ƃ����֐��Ƃ��Ď����Ă���

#pragma once

#include "main.h"


//���ƍ���(XMFLOAT���Ɠ����悤�Ɏg����)
struct WHSIZE {
	float w;	//��
	float h;	//����

	//WHSIZE(0.0f,0.0f);�݂����Ȋ����ő���o����悤��
	WHSIZE() = default;

	WHSIZE(const WHSIZE&) = default;
	WHSIZE& operator=(const WHSIZE&) = default;

	WHSIZE(WHSIZE&&) = default;
	WHSIZE& operator=(WHSIZE&&) = default;

	constexpr WHSIZE(float _w, float _h) : w(_w), h(_h) {}
	explicit WHSIZE(_In_reads_(2) const float* pArrah) : w(pArrah[0]), h(pArrah[1]) {}
};




void OutputDebug(const char* format, ...);

//XY��XYZ�̉�]�ɕϊ����ĉ��Z
void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset);

//XMFLOAT3���m�̑����Z
XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̈����Z
XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̊|���Z
XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);
//XMFLOAT3���m�̊���Z
XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//�����̒l��XMFLOAT�R������������
XMFLOAT3 SetXMFLOAT3(float set);

//�l�̍ő�l�ƍŏ��l���w��o����
float Clamp(float value, float min, float max);

// ����(dot)
float DotProduct(XMVECTOR* v1, XMVECTOR* v2);
// �O��(cross)
void CrossProduct(XMVECTOR* ret, XMVECTOR* v1, XMVECTOR* v2);

// XMFLOAT3 ���K��
XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3 vf3);

//XMFLOAT3�̔�r
bool ComparisonXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

//��_�Ԃ̋����i���j
float LengthXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);


//BB�̓����蔻��i��]�͎w��ł��Ȃ��j
//�������Ă�����True��Ԃ�
bool CollisionBB(XMFLOAT3 pos1, WHSIZE size1, XMFLOAT3 pos2, WHSIZE size2);
//BC�̓����蔻��
//�������Ă�����True��Ԃ�
bool CollisionBC(XMFLOAT3 pos1, float r1, XMFLOAT3 pos2, float r2);