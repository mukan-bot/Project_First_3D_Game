//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "result_ui.h"
#include "input.h"
#include "input_M.h"
#include "text.h"

//�}�N����`
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// �I������Ă��Ȃ��Ƃ��̐F
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// �I������Ă��鎞�̐F

#define TEXT_SIZE1	(40)	// �I������Ă��Ȃ��Ƃ��̃T�C�Y
#define TEXT_SIZE2	(50)	// �I������Ă��鎞�̃T�C�Y

#define MENUE_TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define MENUE_TEXT_POS_Y		(250)				// �e�L�X�g��Y�̍��W
#define MENUE_TEXT_POS_Y_PLUS	(80)				// �e�L�X�g��Y�̍��W�̍�


enum MENUE {
	BACK_TO_TITLE,
	RESTART,
	EXIT,
	MENUE_MAX,
};


static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
//static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = { {"�a�`�b�j �s�n �s�h�s�k�d"},
										{"�q�d�r�s�`�q�s"},
										{"�d�w�h�s"}
};

HRESULT InitResultUI(void) {
	SetCursorMove(true);	//�J�[�\���𓮂��悤�ɂ��Ă���

	//�e�L�X�g�̋��ʂ̏�Ԃ�ݒ�
	for (int i = 0; i < MENUE_MAX; i++) {
		g_menueTextParameter[i].color = TEXT_COLOR1;
		g_menueTextParameter[i].size = TEXT_SIZE1;
		g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
	}
	g_menueSelect = 0;


	return S_OK;
}
void UninitResultUI(void) {
}
void UpdateResultUI(void) {

	// �I������Ă��镨��ύX����
	if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
	if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

	g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);	//�I���ł��镨�ȊO�̂Ƃ���ɂ����Ȃ��悤�ɂ���

	// �I���̌���
	if (GetInputTrigger(MOVE_JUMP)) {
		switch (g_menueSelect)
		{
		case BACK_TO_TITLE: // �^�C�g���ɖ߂�
			SetMode(MODE_TITLE);
			break;
		case RESTART: // �Q�[���ɍs��
			SetMode(MODE_GAME);
			break;
		case EXIT: // �I������
			PostQuitMessage(0);
			break;
		case MENUE_MAX:
			break;
		default:
			break;
		}
	}

}

void DrawResultUI(void) {
	//�I������Ă��镶���̐F�ƃT�C�Y��ς���B
	for (int i = 0; i < MENUE_MAX; i++) {
		g_menueTextParameter[i].color = TEXT_COLOR1;
		g_menueTextParameter[i].size = TEXT_SIZE1;
		g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
	}
	g_menueTextParameter[g_menueSelect].color = TEXT_COLOR2;
	g_menueTextParameter[g_menueSelect].size = TEXT_SIZE2;

	for (int i = 0; i < MENUE_MAX; i++) {
		SetText(g_menueTextParameter[i], g_menueText[i]);
	}

	// ���ʂ̔��\
	TEXT text;
	text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	text.size = 80;
	//�Q�[�����N���A�������ǂ����ŕ\����؂�ւ���
	if (GetIsClear()) {
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		SetText(text, "�Q�[���N���A�[");
	}
	else {
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		SetText(text, "�Q�[���I�[�o�[");
	}
}