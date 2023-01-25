//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "enemy.h"
#include "player.h"
#include "collision.h"
#include "attack.h"
#include "sound.h"
#include "sprite.h"
#include "camera.h"


#define MODEL_PATH			("./data/MODEL/Skull/skull.obj")
#define MODEL_PARTS_PATH	("./data/MODEL/Skull/jaw.obj")

#define MOVE_ROT_ANGLE		(180)
#define MOVE_ROT_SPEED		(30)
#define MOVE_LENGTH			(10)
#define MOVE_FRONT_SPEED	(30)

#define ATK_DELAY		(60)	//�v���C���[�������Ă���(�����J���Ă���)60F��ɍU���𔭎�
#define LOOK_PLAYER		(XMFLOAT3(40.0f,40.0f,40.0f))	//�v���C���[��T�m�ł���͈�

#define BAR_TEXTURE			("./data/TEXTURE/WhiteOut.png")	// �o�[�̃e�N�X�`���[�i�F�ς��Ŏg�p�j
#define BAR_SIZE_WIDTH		(6)	// �o�[�̃T�C�Y��
#define BAR_SIZE_HEIGHT		(1)	// �o�[�̃T�C�Y�c
#define BAR_OFFSET_Y		(4)		// �o�[��\��������W��offset
#define BAR_COLOR_1			(XMFLOAT4(1.0f,0.0f,0.0f,1.0f))	// HP�o�[�̉��̐F
#define BAR_COLOR_2			(XMFLOAT4(0.0f,1.0f,0.0f,1.0f))	// HP�o�[�̎c��
#define BAR_SHOW_LEN		(45)	// �o�[���\������鋗���iPLAYER�ƃG�l�~�[�ԁj

#define ENEMY_DEATH_COUNT	(60)	// �G�l�~�[�̎��S�V�[���̒���
enum ENEMY_STATE{
	ENEMY_STOP,
	ENEMY_ROTATION,
	ENEMY_CALCULATION,
	ENEMY_MOVE,
	ENEMY_ATK,
	ENEMY_DEATH,
	ENEMY_STATE_MAX
};


struct ENEMY{
	bool use;
	bool isMove;	//�ړ���Ԃ��ǂ���
	int objIndex;
	int colIndex;
	int hitColIndex;
	int modelIndex;
	int modelPartsIndex;
	int objPartsIndex;
	int HP;
	//�s��pattern����邽�߂Ɏg��
	ENEMY_STATE state;
	int count;
	//�ړ��Ƃ���]�Ɏg��
	XMFLOAT3 rot;
	XMFLOAT3 pos1;
	XMFLOAT3 pos2;
	XMFLOAT3 vec;
	//�R���W������offset
	XMFLOAT3 c_pos;
	XMFLOAT3 c_size;
	//�U��
	bool isATK;		//�U�����Ă邩
	int atkCount;	//�U���܂ł̃J�E���g�_�E��

	//HP�o�[�̕\��
	WHSIZE barSize;
	MATERIAL material;
	ID3D11Buffer* vertexBuffer1;	//HP�o�[�̎c�ʂ̒��_�o�b�t�@�[
	ID3D11Buffer* vertexBuffer2;	//HP�o�[�̎c�ʂ̒��_�o�b�t�@�[
};


//�O���[�o���ϐ�
ENEMY g_enemy[20];
int g_pObjectIndex;	// �v���C���[�̃I�u�W�F�N�g�C���f�b�N�X������
XMFLOAT3 g_pPos;	// �v���C���[�̍��W��ۑ�����

static ID3D11Buffer* g_VertexBuffer = NULL;	//HP�o�[�̑S�̗ʂ̒��_�o�b�t�@


static ID3D11ShaderResourceView* g_Texture = NULL;


//�v���g�^�C�v�錾
void LookPlayer(ENEMY* enemy);	// �v���C���[���߂��ɗv�邩�𔻒f
HRESULT MakeVertexEnemyHpBar(ID3D11Buffer** vertexBuffer, float fWidth, float fHeight);

HRESULT InitEnemy(void) {

	g_pObjectIndex = GetPlayerGameObjectIndex();

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].objIndex = SetGameObject();
		SetPosition(g_enemy[i].objIndex, XMFLOAT3(0.0f, -1000.0f, 0.0f));	//�����Ȃ����ɐ������Ă���
		g_enemy[i].modelIndex = SetGameModel(MODEL_PATH, g_enemy[i].objIndex, 0, CULL_MODE_BACK);

		g_enemy[i].objPartsIndex = SetGameObject();
		SetGameObjectParent(g_enemy[i].objPartsIndex, g_enemy[i].objIndex);
		g_enemy[i].modelPartsIndex = SetGameModel(MODEL_PARTS_PATH, g_enemy[i].objPartsIndex, 0, CULL_MODE_BACK);
		SetGameObjectZERO(g_enemy[i].objPartsIndex);

		g_enemy[i].colIndex = SetCollision(LAYER_OBSTACLE, TYPE_BB);
		g_enemy[i].hitColIndex = SetCollision(LAYER_ENEMY, TYPE_BC);

		g_enemy[i].c_size = XMFLOAT3(0.5f, 0.5f, 0.5f);	//collision�̃T�C�Y
		g_enemy[i].c_pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
		g_enemy[i].HP = 100;
		g_enemy[i].use = false;

		g_enemy[i].state = ENEMY_STOP;
		g_enemy[i].rot = SetXMFLOAT3(0.0f);
		g_enemy[i].count = 0;

		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);
		int index;
		index = GetColObjectIndex(g_enemy[i].colIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));
		index = GetColObjectIndex(g_enemy[i].hitColIndex);
		SetPosition(index, pos);
		SetRotation(index, rot);
		SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

		// ���_�o�b�t�@����
		//MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer1, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);
		//MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer2, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);

		// �}�e���A��
		ZeroMemory(&g_enemy[i].material, sizeof(g_enemy[i].material));
		g_enemy[i].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_enemy[i].material.DissolveAlpha = 1.0f;
	}
	// ���_�o�b�t�@����
	MakeVertexEnemyHpBar(&g_VertexBuffer, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);
	//HP�o�[�p�̃e�N�X�`���̓ǂݍ���
	g_Texture = NULL;
	D3DX11CreateShaderResourceViewFromFile(GetDevice(), BAR_TEXTURE, NULL, NULL, &g_Texture, NULL);

	return S_OK;
}

void UninitEnemy(void) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].use = false;
		DelCollision(g_enemy[i].colIndex);
		DelCollision(g_enemy[i].hitColIndex);
		DelGameObject(g_enemy[i].objIndex);
		DelGameObject(g_enemy[i].objPartsIndex);
	}
}

void UpdateEnemy(void) {

	//���[�v�O�łł��邱�Ƃ̓��[�v�̊O�ł��
	g_pPos = GetPosition(g_pObjectIndex);
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].use) continue;

		XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);
		XMFLOAT3 rot = GetRotation(g_enemy[i].objIndex);
		XMFLOAT3 scl = GetScale(g_enemy[i].objIndex);

		bool isOK = true;

		//�p�[�c
		{
			SetGameObjectZERO(g_enemy[i].objPartsIndex);	// �ꉞ�O�ɂ��Ă���
			if (g_enemy[i].isATK) {							// �U����������������J���郂�[�V����������
				SetPosition(g_enemy[i].objPartsIndex, XMFLOAT3(0.0f, -0.2f, 0.0f));
				SetRotation(g_enemy[i].objPartsIndex, XMFLOAT3(-0.5f, 0.0f, 0.0f));
			}
		}

		// �G�l�~�[���U��������Ȃ��܂��͎���łȂ��Ȃ�U���ł���͈͂Ƀv���C���[�����邩�m�F
		if (g_enemy[i].state != ENEMY_ATK) {
			LookPlayer(&g_enemy[i]);
		}


		//�ړ�
		{
			switch (g_enemy[i].state)
			{
			case ENEMY_STOP:// ��]�ʂ��v�Z
				g_enemy[i].rot.y = DegToRad(((rand() % MOVE_ROT_ANGLE) - MOVE_ROT_ANGLE / 2) / MOVE_ROT_SPEED);
				g_enemy[i].state = ENEMY_ROTATION;
				g_enemy[i].count = MOVE_ROT_SPEED;
				break;
			case ENEMY_ROTATION:// �G�l�~�[����]
				if (g_enemy[i].count > 0) {
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].count--;
				}
				else {
					g_enemy[i].state = ENEMY_CALCULATION;
				}
				break;
			case ENEMY_CALCULATION:// �ړ��ł��邩�v�Z
				g_enemy[i].pos1 = g_enemy[i].pos2 = GetPosition(g_enemy[i].objIndex);
				
				for (int j = 0; j < MOVE_LENGTH; j++) {
					g_enemy[i].pos2.x += sinf(rot.y);
					g_enemy[i].pos2.z += cosf(rot.y);
					SetPosition(GetColObjectIndex(g_enemy[i].colIndex), g_enemy[i].pos2);
					if (GetColAnsUpdate(g_enemy[i].colIndex)) {
						g_enemy[i].state = ENEMY_STOP;
						isOK = false;
						break;
					}
				}
				if (isOK) {
					g_enemy[i].state = ENEMY_MOVE;
					g_enemy[i].vec = SubXMFLOAT3(g_enemy[i].pos2, g_enemy[i].pos1);
					g_enemy[i].vec = DivXMFLOAT3(g_enemy[i].vec, SetXMFLOAT3(MOVE_FRONT_SPEED));
					g_enemy[i].count = MOVE_FRONT_SPEED;
				}
				SetPosition(GetColObjectIndex(g_enemy[i].colIndex), g_enemy[i].pos1);	//�R���W�����̏ꏊ�����ɖ߂�
				break;
			case ENEMY_MOVE:// �ړ�
				if (g_enemy[i].count > 0) {
					pos.x += g_enemy[i].vec.x;
					pos.y += g_enemy[i].vec.y;
					pos.z += g_enemy[i].vec.z;
					g_enemy[i].count--;

				}
				else {
					g_enemy[i].state = ENEMY_CALCULATION;
				}
				break;
			case ENEMY_ATK:// �U��
				if (g_enemy[i].atkCount < 0) {
					if (g_enemy[i].atkCount > -30) {
						SetAttack(ATK_ENEMY_1, g_enemy[i].objIndex);	//MEMO:��������Ƃ��΂炭���̒��ɗ��܂��Ă���悤�Ɍ�����͂�
					}
					if(g_enemy[i].atkCount < -ATK_DELAY) {
						g_enemy[i].state = ENEMY_CALCULATION;
						g_enemy[i].isATK = false;
					}
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].rot.y -= 0.01f;
					g_enemy[i].atkCount--;
				}
				else {	//ATK_DELAY�̉񐔕��҂�
					g_enemy[i].atkCount--;
					//��]������i���X�ɑ����j
					rot.y += g_enemy[i].rot.y;
					g_enemy[i].rot.y += 0.01f;
				}
				break;
			case ENEMY_DEATH:
				if (g_enemy[i].count < 0) {
					DelGameObject(g_enemy[i].objIndex);
					DelGameModel(g_enemy[i].modelIndex);
					DelGameModel(g_enemy[i].modelPartsIndex);
					DelGameObject(g_enemy[i].objPartsIndex);
					g_enemy[i].use = false;
				}
				else {
					g_enemy[i].count--;
					float a = GetGameModelDissolve(g_enemy[i].modelIndex);
					a -= 1.0f / ENEMY_DEATH_COUNT;
					OutputDebug("%f", a);
					SetGameModelDissolve(g_enemy[i].modelIndex, a);
					SetGameModelDissolve(g_enemy[i].modelPartsIndex, a);
				}
				break;
			case ENEMY_STATE_MAX:
				break;
			default:
				break;
			}
			//�X�V
			SetPosition(g_enemy[i].objIndex, pos);
			SetRotation(g_enemy[i].objIndex, rot);
			SetScale(g_enemy[i].objIndex, scl);

		}



		//�����蔻��
		{
			if (g_enemy[i].HP > -1) {
				int index;
				index = GetColObjectIndex(g_enemy[i].colIndex);
				SetPosition(index, AddXMFLOAT3(pos, g_enemy[i].c_pos));
				SetRotation(index, rot);
				SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));
				index = GetColObjectIndex(g_enemy[i].hitColIndex);
				SetPosition(index, AddXMFLOAT3(pos, g_enemy[i].c_pos));
				SetRotation(index, rot);
				SetScale(index, MulXMFLOAT3(scl, g_enemy[i].c_size));

				if (GetColAnsUpdate(g_enemy[i].hitColIndex)) {
					g_enemy[i].HP--;
				}
				if (g_enemy[i].HP <= 0) {
					//HP���O�ɂȂ����特��炵�ăG�l�~�[���폜����
					g_enemy[i].state = ENEMY_DEATH;
					g_enemy[i].count = ENEMY_DEATH_COUNT;

					DelCollision(g_enemy[i].colIndex);
					DelCollision(g_enemy[i].hitColIndex);

					PlaySound(SOUND_LABEL_SE_wana3);
				}
			}
		}




	}

	//�N���A����
	bool isAllKill = false;
	//���ׂẴG�l�~�[������ł��邩
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) {
			isAllKill = false;
			break;
		}
		else {
			isAllKill = true;
		}
	}
	if (isAllKill) {// ���ׂĐ����Ă��Ȃ�������N���A�Ń��U���g�ɔ�΂�
		SetIsClear(isAllKill);
		SetMode(MODE_RESULT);
	}
}
void DrawEnemy(void) {
	XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
	XMFLOAT4X4 camMtxView = GetCameraMtxView();

	SetAlphaTestEnable(true);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int Pindex = GetPlayerGameObjectIndex();
	XMFLOAT3 pPos = GetPosition(Pindex);

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) {

			if (g_enemy[i].state == ENEMY_DEATH) continue;

			float len = LengthXMFLOAT3(pPos, GetPosition(g_enemy[i].objIndex));

			if (len < BAR_SHOW_LEN) {

				//HP�o�[�̉��n�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
				MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer1, BAR_SIZE_WIDTH, BAR_SIZE_HEIGHT);	// ������HP�̎c�ʂɍ��킹��

				// ���_�o�b�t�@�ݒ�
				stride = sizeof(VERTEX_3D);
				offset = 0;
				GetDeviceContext()->IASetVertexBuffers(0, 1, &g_enemy[i].vertexBuffer1, &stride, &offset);

				//�F�̕ύX
				g_enemy[i].material.Diffuse = BAR_COLOR_1;

				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

				XMFLOAT3 pos = GetPosition(g_enemy[i].objIndex);

				// ���[���h�}�g���b�N�X�̏�����
				mtxWorld = XMMatrixIdentity();

				// �r���[�}�g���b�N�X���擾
				mtxView = XMLoadFloat4x4(&camMtxView);


				mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
				mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
				mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

				mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
				mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
				mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

				mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
				mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
				mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

				// �ړ��𔽉f
				pos.y += BAR_OFFSET_Y;
				mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
				mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

				// ���[���h�}�g���b�N�X�̐ݒ�
				SetWorldMatrix(&mtxWorld);

				// �}�e���A���ݒ�
				SetMaterial(g_enemy[i].material);

				// �|���S���̕`��
				GetDeviceContext()->Draw(4, 0);


				//HP�o�[�̎c�ʂ̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
				// ���_�o�b�t�@����
				MakeVertexEnemyHpBar(&g_enemy[i].vertexBuffer2, -BAR_SIZE_WIDTH + ((BAR_SIZE_WIDTH * (g_enemy[i].HP / 100.0f)) * 2), BAR_SIZE_HEIGHT);	// ������HP�̎c�ʂɍ��킹��
				// ���_�o�b�t�@�ݒ�
				stride = sizeof(VERTEX_3D);
				offset = 0;
				GetDeviceContext()->IASetVertexBuffers(0, 1, &g_enemy[i].vertexBuffer2, &stride, &offset);
				//�F�̕ύX
				g_enemy[i].material.Diffuse = BAR_COLOR_2;

				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);

				pos = GetPosition(g_enemy[i].objIndex);

				// ���[���h�}�g���b�N�X�̏�����
				mtxWorld = XMMatrixIdentity();

				// �r���[�}�g���b�N�X���擾
				mtxView = XMLoadFloat4x4(&camMtxView);

				mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
				mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
				mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

				mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
				mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
				mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

				mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
				mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
				mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

				// �ړ��𔽉f
				pos.y += BAR_OFFSET_Y;
				mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
				mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

				// ���[���h�}�g���b�N�X�̐ݒ�
				SetWorldMatrix(&mtxWorld);

				// �}�e���A���ݒ�
				SetMaterial(g_enemy[i].material);

				// �|���S���̕`��
				GetDeviceContext()->Draw(4, 0);

			}

		}
	}

	SetAlphaTestEnable(false);

}

void SetEnemy(XMFLOAT3 pos,XMFLOAT3 rot, XMFLOAT3 scl) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) continue;
		//�G�l�~�[��ǂݍ��ނ̂͂ł��Ă邩��use�ƍ��W��]�傫��������������
		SetPosition(g_enemy[i].objIndex, pos);
		SetRotation(g_enemy[i].objIndex, rot);
		SetScale(g_enemy[i].objIndex, scl);

		g_enemy[i].use = true;
		break;
	}
}

int GetAliveEnemy(void) {
	int ans = 0;
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].use) ans++;
	}
	return ans;
}


void LookPlayer(ENEMY* enemy) {
	if (enemy->state == ENEMY_DEATH) return;

	//�G�l�~�[�̍U���̃N�[���_�E�����I����Ă�����V�����U��������
	if (enemy->atkCount > 0) {
		if (CollisionBB(GetPosition(enemy->objIndex), LOOK_PLAYER, g_pPos, LOOK_PLAYER)) {
			enemy->isATK = true;
			enemy->state = ENEMY_ATK;
			enemy->atkCount = ATK_DELAY;
			XMFLOAT3 pos = GetPosition(enemy->objIndex);
			XMFLOAT3 rot = GetRotation(enemy->objIndex);

			enemy->rot.y = 0.01f;

		}
	}
	// �N�[���_�E���܂�
	else {
		enemy->atkCount++;
	}
}


int GetEnemyIndex(int index) {
	if (g_enemy[index].use) {
		return g_enemy[index].objIndex;
	}
	return -1;
}

int GetEnemyHP(int index) {
	return g_enemy[index].HP;
}

void SetEnemyHP(int index, int hp) {
	g_enemy[index].HP = hp;
}


// ���_���̍쐬
HRESULT MakeVertexEnemyHpBar(ID3D11Buffer** vertexBuffer, float fWidth, float fHeight) {
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, vertexBuffer);

	// ���_�o�b�t�@�ɒl���Z�b�g����
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(*vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// ���_���W�̐ݒ�

	vertex[0].Position = XMFLOAT3(-BAR_SIZE_WIDTH / 2, 0, 0.0f);
	vertex[1].Position = XMFLOAT3(fWidth / 2, 0, 0.0f);
	vertex[2].Position = XMFLOAT3(-BAR_SIZE_WIDTH / 2, -fHeight, 0.0f);
	vertex[3].Position = XMFLOAT3(fWidth / 2, -fHeight, 0.0f);

	// �g�U���̐ݒ�
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	GetDeviceContext()->Unmap(*vertexBuffer, 0);

	return S_OK;
}