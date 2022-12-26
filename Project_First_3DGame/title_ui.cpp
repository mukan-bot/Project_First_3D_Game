#include "title_ui.h"
#include "input.h"
#include "text.h"

//�}�N����`
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// �I������Ă��Ȃ��Ƃ��̐F
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// �I������Ă��鎞�̐F

#define TEXT_SIZE1	(40)	// �I������Ă��Ȃ��Ƃ��̃T�C�Y
#define TEXT_SIZE2	(50)	// �I������Ă��鎞�̃T�C�Y

#define TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define TEXT_POS_Y		(250)				// �e�L�X�g��Y�̍��W
#define TEXT_POS_Y_PLUS	(80)				// �e�L�X�g��Y�̍��W�̍�

enum MENUE {
	START,
	OPTION,
	EXIT,
	MENUE_MAX,
};


static TEXT g_textParameter[MENUE_MAX];
static int g_select;
static char g_text[MENUE_MAX][128] = {	{"�r�s�`�q�s"},
										{"�n�o�s�h�n�m"},
										{"�d�w�h�s"} };

HRESULT InitTitleUI(void) {

	for (int i = 0; i < MENUE_MAX; i++) {
		g_textParameter[i].color = TEXT_COLOR1;
		g_textParameter[i].size = TEXT_SIZE1;
		g_textParameter[i].pos = XMFLOAT2((float)TEXT_POS_X, (float)(TEXT_POS_Y + (i * TEXT_POS_Y_PLUS)));
	}

	g_select = 0;

	return S_OK;
}
void UninitTitleUI(void) {
}
void UpdateTitleUI(void) {

	// �I������Ă��镨��ύX����
	if (GetInputTrigger(MOVE_FRONT)) g_select--;
	if (GetInputTrigger(MOVE_BACK)) g_select++;

	g_select = (int)Clamp((float)g_select, 0.0, (float)MENUE_MAX-1);


	if (GetInputTrigger(MOVE_JUMP)) {
		switch (g_select)
		{
		case START:
			SetMode(MODE_GAME);
			break;
		case OPTION:
			
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

void DrawTitleUI(void) {

	//�I������Ă��镶���̐F�ƃT�C�Y��ς���B
	for (int i = 0; i < MENUE_MAX; i++) {
		g_textParameter[i].color = TEXT_COLOR1;
		g_textParameter[i].size = TEXT_SIZE1;
		g_textParameter[i].pos = XMFLOAT2((float)TEXT_POS_X, (float)(TEXT_POS_Y + (i * TEXT_POS_Y_PLUS)));
	}
	g_textParameter[g_select].color = TEXT_COLOR2;
	g_textParameter[g_select].size = TEXT_SIZE2;


	
	for (int i = 0; i < MENUE_MAX; i++) {
		SetText(g_textParameter[i], g_text[i]);
	}

}