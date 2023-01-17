//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "attack.h"
#include "collision.h"
#include "particle.h"
#include "UI.h"
#include "light.h"
#include "sound.h"

#include "player.h"

#define ATK_MAX	(125)

#define ENEMY_ATK_SPEED	(30.00f)



//�O���[�o���ϐ�
ATTACK g_atk[ATK_MAX];

//�v���g�^�C�v�錾
void DelAtack(int index);

HRESULT InitAttack(void) {
	for (int i = 0; i < ATK_MAX; i++) {
		g_atk[i].use = false;
	}
	return S_OK;
}
void UninitAttack(void) {

}
void UpdateAttack(void) {
	for (int i = 0; i < ATK_MAX; i++) {
		if (!g_atk[i].use) continue;// �g���ĂȂ��Ȃ��΂�

		int index = g_atk[i].colObjIndex; // �g���₷���悤��


		// �ݒ�t���[������������폜
		if (g_atk[i].countFlame >= g_atk[i].maxFlame) {
			DelAtack(i);
			continue;
		}

		// ����������폜
		if (GetColAns(g_atk[i].colIndex)) {
			DelAtack(i);
			// �v���C���[�̍U�����G�l�~�[�̍U�����Ŗ炷����ς���
			if (g_atk[i].type == ATK_ENEMY_1 || g_atk[i].type == ATK_ENEMY_2) {
				PlaySound(SOUND_LABEL_SE_select1);
			}
			else {
				PlaySound(SOUND_LABEL_SE_select2);
			}
			continue;
		}
		

		// �K�v�ȏ�������
		XMFLOAT3 pos = GetPosition(index);
		XMFLOAT3 rot = GetRotation(index);

		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f);

		switch (g_atk[i].type)
		{
		//�v���C���[�͎̂��_�ɍ��킹�Ĉړ�������
		case(ATK_PLAYER_1):
		case(ATK_PLAYER_2):
			vec.x += sinf(rot.x);
			vec.z += cosf(rot.x);
			vec.y -= tanf(rot.z);

			vec = NormalizeXMFLOAT3(vec);

			pos = AddXMFLOAT3(pos, vec);
			SetPosition(index, pos);
			break;
		//ENEMY�̂͐ݒu�����^�C�~���O�̃v���C���[�̍��W�ֈړ��i�j
		case(ATK_ENEMY_1):
		case(ATK_ENEMY_2):
			pos = AddXMFLOAT3(pos, g_atk[i].vec);
			SetPosition(index, pos);
			break;
		default:
			break;
		}

		// �����蔻�莗���킹�ăt�B�[���h�̓����蔻���������
		index = g_atk[i].fieldColObjIndex;
		SetPosition(index, pos);

		// �t�B�[���h�̓����蔻������Ă������Ă�����폜
		if (GetColAns(g_atk[i].fieldColIndex)) {
			DelAtack(i);
			continue;
		}
		g_atk[i].countFlame++;
	}
}
void DrawAttack(void) {
	// �p�[�e�B�N���Ƃ�GameModel�ŕ\������̂ŉ����Ȃ�
}

void SetAttack(ATK_TYPE type, int objIndex) {

	//�K�v�ȏ��̎��o��
	XMFLOAT3 pos = GetPosition(objIndex);
	XMFLOAT3 rot = GetRotation(objIndex);
	XMFLOAT3 scl = GetScale(objIndex);

	for (int i = 0; i < ATK_MAX; i++) {
		if (g_atk[i].use) continue;

		//���ʂ̏�����
		g_atk[i].countFlame = 0;

		g_atk[i].type = type;

		int index = -1;

		// �U���̎�ނ��Ƃɏ����ݒ������
		switch (type)
		{
		case ATK_PLAYER_1:
			g_atk[i].maxFlame = 60;

			g_atk[i].colIndex = SetCollision(LAYER_PLAYER_ATK, TYPE_BC);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.01f, 0.01f, 0.01f));

			//�t�B�[���h�Ƃ̓����蔻��
			g_atk[i].fieldColIndex = SetCollision(LAYER_FIELD, TYPE_BB);
			index = g_atk[i].fieldColObjIndex = GetColObjectIndex(g_atk[i].fieldColIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.001f, 0.001f, 0.001f));

			//������
			SetParticle(g_atk[i].colObjIndex, PLAYER_ATK1, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			


			break;

		case ATK_PLAYER_2:
			g_atk[i].maxFlame = 5;
			g_atk[i].colIndex = SetCollision(LAYER_PLAYER_ATK, TYPE_BC);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.1f, 0.1f, 0.1f));
			break;

		case ATK_ENEMY_1:
			g_atk[i].maxFlame = 120;
			g_atk[i].colIndex = SetCollision(LAYER_ENEMY_ATK, TYPE_BC);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.05f, 0.05f, 0.05f));

			//�t�B�[���h�Ƃ̓����蔻��
			g_atk[i].fieldColIndex = SetCollision(LAYER_FIELD, TYPE_BB);
			index = g_atk[i].fieldColObjIndex = GetColObjectIndex(g_atk[i].fieldColIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(0.001f, 0.001f, 0.001f));

			//������
			SetParticle(g_atk[i].colObjIndex, PLAYER_ATK1, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));

			g_atk[i].vec = SubXMFLOAT3(GetPosition(GetPlayerGameObjectIndex()), GetPosition(objIndex));
			g_atk[i].vec = DivXMFLOAT3(g_atk[i].vec, SetXMFLOAT3(ENEMY_ATK_SPEED));


			break;

		case ATK_ENEMY_2:
			g_atk[i].maxFlame = 120;
			g_atk[i].colIndex = SetCollision(LAYER_ENEMY_ATK, TYPE_BB);
			index = g_atk[i].colObjIndex = GetColObjectIndex(g_atk[i].colIndex);
			SetPosition(index, pos);
			SetRotation(index, rot);
			SetScale(index, XMFLOAT3(1.0f, 1.0f, 1.0f));

			g_atk[i].vec = SubXMFLOAT3(GetPosition(GetPlayerGameObjectIndex()), GetPosition(objIndex));
			g_atk[i].vec = DivXMFLOAT3(g_atk[i].vec, SetXMFLOAT3(ENEMY_ATK_SPEED));

			break;
		}

		//�R���W�����������Ɛݒu�ł��Ă邩�`�F�b�N
		if (g_atk[i].colIndex == -1 || index == -1) {
			break;
		}



		g_atk[i].use = true;

		break;
	}
}

void DelAtack(int index) {
	//�g���������폜����
	DelCollision(g_atk[index].colIndex);
	DelCollision(g_atk[index].fieldColIndex);
	g_atk[index].use = false;
}

