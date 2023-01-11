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
#define MENUE_TEXT_POS_Y		(350)				// �e�L�X�g��Y�̍��W
#define MENUE_TEXT_POS_Y_PLUS	(80)				// �e�L�X�g��Y�̍��W�̍�

#define OPTION_TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define OPTION_TEXT_POS_Y		(100)				// �e�L�X�g��Y�̍��W
#define OPTION_TEXT_POS_Y_PLUS	(80)				// �e�L�X�g��Y�̍��W�̍�

enum MENUE {
	BACK_TO_TITLE,
	RESTART,
	EXIT,
	MENUE_MAX,
};

enum OPTION_MENUE {
	BGM_VOLUME,
	SE_VOLUME,
	LOOK_SENSITIVE,
	BACK,
	OPTION_MAX,
};


static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = { {"�a�`�b�j �s�n �s�h�s�k�d"},
										{"�q�d�r�s�`�q�s"},
										{"�d�w�h�s"}
};
static TEXT g_optionTextParameter[OPTION_MAX];
static int g_optionSelect;
static char g_optionText[OPTION_MAX][128] = { {"�a�f�l�@�u�n�k�t�l�d"},{"�r�d�@�u�n�k�t�l�d"},{"�k�n�n�j�@�r�d�m�r�h�s�h�u�d"},{"�a�`�b�j"} };

HRESULT InitResultUI(void) {
	SetCursorMove(true);	//�J�[�\���𓮂��悤�ɂ��Ă���
	for (int i = 0; i < MENUE_MAX; i++) {
		g_menueTextParameter[i].color = TEXT_COLOR1;
		g_menueTextParameter[i].size = TEXT_SIZE1;
		g_menueTextParameter[i].pos = XMFLOAT2((float)MENUE_TEXT_POS_X, (float)(MENUE_TEXT_POS_Y + (i * MENUE_TEXT_POS_Y_PLUS)));
	}
	g_menueSelect = 0;

	for (int i = 0; i < OPTION_MAX; i++) {
		g_optionTextParameter[i].color = TEXT_COLOR1;
		g_optionTextParameter[i].size = TEXT_SIZE1;
		g_optionTextParameter[i].pos = XMFLOAT2((float)OPTION_TEXT_POS_X, (float)(OPTION_TEXT_POS_Y + (i * OPTION_TEXT_POS_Y_PLUS)));
	}
	g_optionSelect = 0;

	return S_OK;
}
void UninitResultUI(void) {
}
void UpdateResultUI(void) {

	// �I������Ă��镨��ύX����
	if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
	if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

	g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);

	// �I���̌���
	if (GetInputTrigger(MOVE_JUMP)) {
		switch (g_menueSelect)
		{
		case BACK_TO_TITLE:
			SetMode(MODE_TITLE);
			break;
		case RESTART:
			SetMode(MODE_GAME);
			break;
		case EXIT:
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

	if (!g_isOption) {
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
	}

	else {
		//�I������Ă��镶���̐F�ƃT�C�Y��ς���B
		for (int i = 0; i < OPTION_MAX; i++) {
			g_optionTextParameter[i].color = TEXT_COLOR1;
			g_optionTextParameter[i].size = TEXT_SIZE1;
			g_optionTextParameter[i].pos = XMFLOAT2((float)OPTION_TEXT_POS_X, (float)(OPTION_TEXT_POS_Y + (i * OPTION_TEXT_POS_Y_PLUS)));
		}
		g_optionTextParameter[g_optionSelect].color = TEXT_COLOR2;
		g_optionTextParameter[g_optionSelect].size = TEXT_SIZE2;


		for (int i = 0; i < OPTION_MAX; i++) {
			SetText(g_optionTextParameter[i], g_optionText[i]);
		}
	}

}