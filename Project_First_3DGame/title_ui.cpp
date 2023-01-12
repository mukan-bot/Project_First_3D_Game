//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "title_ui.h"
#include "input.h"
#include "input_M.h"
#include "text.h"
#include "sound.h"

//�}�N����`
#define TEXT_COLOR1 (XMFLOAT4(0.5f, 0.5f, 0.5f, 0.8f))	// �I������Ă��Ȃ��Ƃ��̐F
#define TEXT_COLOR2 (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))	// �I������Ă��鎞�̐F

#define TEXT_SIZE1	(40)	// �I������Ă��Ȃ��Ƃ��̃T�C�Y
#define TEXT_SIZE2	(50)	// �I������Ă��鎞�̃T�C�Y

#define MENUE_TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define MENUE_TEXT_POS_Y		(250)				// �e�L�X�g��Y�̍��W
#define MENUE_TEXT_POS_Y_PLUS	(80)				// �e�L�X�g��Y�̍��W�̍�

#define OPTION_TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define OPTION_TEXT_POS_Y		(50)				// �e�L�X�g��Y�̍��W
#define OPTION_TEXT_POS_Y_PLUS	(60)				// �e�L�X�g��Y�̍��W�̍�

#define TUTORIAL_TEXT_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define TUTORIAL_TEXT_POS_Y		(50)				// �e�L�X�g��Y�̍��W
#define TUTORIAL_TEXT_POS_Y_PLUS	(30)				// �e�L�X�g��Y�̍��W�̍�
#define TUTORIAL_TEXT_SIZE1	(20)	// �I������Ă��Ȃ��Ƃ��̃T�C�Y
#define TUTORIAL_TEXT_SIZE2	(30)	// �I������Ă��鎞�̃T�C�Y

#define TUTORIAL_TEXT_MAIN	(5)
#define TUTORIAL_TEXT_MAIN_POS_X		(SCREEN_WIDTH / 2)	// �e�L�X�g��X�̍��W
#define TUTORIAL_TEXT_MAIN_POS_Y		(200)				// �e�L�X�g��Y�̍��W
#define TUTORIAL_TEXT_MAIN_POS_Y_PLUS	(70)				// �e�L�X�g��Y�̍��W�̍�
#define TUTORIAL_TEXT_MAIN_SIZE1		(40)	// �I������Ă��Ȃ��Ƃ��̃T�C�Y
#define TUTORIAL_TEXT_MAIN_SIZE2		(50)	// �I������Ă��鎞�̃T�C�Y

enum MENUE {
	START,
	OPTION,
	TUTORIAL,
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

enum TUTORIAL {
	TUTORIAL_KEYBOARD = 0,
	TUTORIAL_D_INPUT,
	TUTORIAL_X_INPUT,
	TUTORIAL_BACK,
	TUTORIAL_MAX,
};

static TEXT g_menueTextParameter[MENUE_MAX];
static int g_menueSelect;
static bool g_isOption;
static char g_menueText[MENUE_MAX][128] = {	{"�r�s�`�q�s"},
										{"�n�o�s�h�n�m"},
										{"�s�t�s�n�q�h�`�k"},
										{"�d�w�h�s"} 
};
static TEXT g_optionTextParameter[OPTION_MAX];
static int g_optionSelect;
static char g_optionText[OPTION_MAX][128] = { {"�a�f�l�@�u�n�k�t�l�d"},
											{"�r�d�@�u�n�k�t�l�d"},
											{"�k�n�n�j�@�r�d�m�r�h�s�h�u�d"},
											{"�a�`�b�j"} };

static TEXT g_tutorialTextParameter[MENUE_MAX];
static int g_tutorialSelect;
static bool g_isTutorial;
static char g_tutorialText[TUTORIAL_MAX][128] = { {"�L�[�{�[�h"},
												{"�c�����������h��������"},
												{"�w�h��������"},
												{"�a�`�b�j"}
};

//option�̃T�E���h�{�����[���Ŏg����tu 
float g_temp_bgm_vol;
float g_temp_se_vol;

HRESULT InitTitleUI(void) {
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

	//�{�����[���̏����l
	g_temp_bgm_vol = 0.1f;
	g_temp_se_vol = 0.1f;
	
	Sound_BGM_Volume(g_temp_bgm_vol);
	Sound_SE_Volume(g_temp_se_vol);

	return S_OK;
}
void UninitTitleUI(void) {
}
void UpdateTitleUI(void) {

	if (g_isOption) {
		int temp = g_optionSelect;
		// �I������Ă��镨��ύX����
		if (GetInputTrigger(MOVE_FRONT)) g_optionSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_optionSelect++;

		g_optionSelect = (int)Clamp((float)g_optionSelect, 0.0, (float)OPTION_MAX - 1);

		if (g_optionSelect != temp)PlaySound(SOUND_LABEL_SE_select1);


		switch (g_optionSelect)
		{
		case BGM_VOLUME:

			if (GetInputPress(MOVE_JUMP)) {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol -= 0.10f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol += 0.10f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
			}
			else {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol -= 0.01f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_bgm_vol += 0.01f;
					g_temp_bgm_vol = Clamp(g_temp_bgm_vol, 0.0f, 1.0f);
					Sound_BGM_Volume(g_temp_bgm_vol);
				}
			}
			break;
		case SE_VOLUME:
			if (GetInputPress(MOVE_JUMP)) {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol -= 0.10f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);
					Sound_SE_Volume(g_temp_se_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol += 0.10f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);
					Sound_SE_Volume(g_temp_se_vol);
				}
			}
			else {
				if (GetInputTrigger(MOVE_LEFT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol -= 0.01f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);
					Sound_SE_Volume(g_temp_se_vol);
				}
				if (GetInputTrigger(MOVE_RIGHT)) {
					PlaySound(SOUND_LABEL_SE_select2);
					g_temp_se_vol += 0.01f;
					g_temp_se_vol = Clamp(g_temp_se_vol, 0.0f, 1.0f);
					Sound_SE_Volume(g_temp_se_vol);
				}
			}
			break;
		case LOOK_SENSITIVE:
			break;
		case BACK:
			if (GetInputTrigger(MOVE_JUMP)) {
				g_isOption = false;
			}
			break;
		case OPTION_MAX:
			break;
		default:
			break;
		}

	}

	else if (g_isTutorial) {
		int temp = g_tutorialSelect;
		// �I������Ă��镨��ύX����
		if (GetInputTrigger(MOVE_FRONT)) g_tutorialSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_tutorialSelect++;

		g_tutorialSelect = (int)Clamp((float)g_tutorialSelect, 0.0, (float)TUTORIAL_MAX - 1);

		if (g_tutorialSelect != temp)PlaySound(SOUND_LABEL_SE_select1);

		// �I���̌���
		if (GetInputTrigger(MOVE_JUMP)) {
			PlaySound(SOUND_LABEL_SE_select2);
			switch (g_tutorialSelect)
			{
			case TUTORIAL_KEYBOARD:
				break;
			case TUTORIAL_D_INPUT:
				break;
			case TUTORIAL_X_INPUT:
				break;
			case TUTORIAL_BACK:
				g_isTutorial = false;
				break;
			case TUTORIAL_MAX:
				break;
			default:
				break;
			}
		}
	}
	else{
		int temp = g_menueSelect;

		// �I������Ă��镨��ύX����
		if (GetInputTrigger(MOVE_FRONT)) g_menueSelect--;
		if (GetInputTrigger(MOVE_BACK)) g_menueSelect++;

		g_menueSelect = (int)Clamp((float)g_menueSelect, 0.0, (float)MENUE_MAX - 1);


		if (g_menueSelect != temp)PlaySound(SOUND_LABEL_SE_select1);

		// �I���̌���
		if (GetInputTrigger(MOVE_JUMP)) {
			PlaySound(SOUND_LABEL_SE_select2);
			switch (g_menueSelect)
			{
			case START:
				//���[�h��ʂ�\��
				TEXT text;
				text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
				text.size = 80;
				SetText(text, "�i�E���[�f�B���O");
				Clear();
				// 2D�̕���`�悷�鏈��
				// Z��r�Ȃ�
				SetDepthEnable(false);
				// ���C�e�B���O�𖳌�
				SetLightEnable(false);
				Draw_text();
				// ���C�e�B���O��L����
				SetLightEnable(true);	//TODO:���C�g�������true�ɕς���
				// Z��r����
				SetDepthEnable(true);
				Present();
				//���[�h��ʂ̂܂܃Q�[�����[�h�ڍs����
				SetMode(MODE_GAME);
				break;
			case OPTION:
				g_optionSelect = 0;
				g_isOption = true;
				break;
			case TUTORIAL:
				g_tutorialSelect = 0;
				g_isTutorial = true;
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

}

void DrawTitleUI(void) {
	//�^�C�g����ʁi�ݒ�j
	if (g_isOption) {

		XMFLOAT2 pos = XMFLOAT2(OPTION_TEXT_POS_X, OPTION_TEXT_POS_Y);

		//�I������Ă��镶���̐F�ƃT�C�Y��ς���B
		for (int i = 0; i < OPTION_MAX; i++) {
			//�I������Ă��镨�̐F�Ƒ傫����ς���
			if (g_optionSelect == i) {
				g_optionTextParameter[g_optionSelect].color = TEXT_COLOR2;
				g_optionTextParameter[g_optionSelect].size = TEXT_SIZE2;
			}
			else {
				g_optionTextParameter[i].color = TEXT_COLOR1;
				g_optionTextParameter[i].size = TEXT_SIZE1;
			}
			//�ꏊ�����߂�
			pos.x += 0.0f;
			pos.y += OPTION_TEXT_POS_Y_PLUS;
			g_optionTextParameter[i].pos = pos;

			SetText(g_optionTextParameter[i], g_optionText[i]);
			//�ꏊ�����߂�
			pos.x += 0.0f;
			pos.y += OPTION_TEXT_POS_Y_PLUS;
			g_optionTextParameter[i].pos = pos;
			switch (i)
			{
			case(BGM_VOLUME):
				SetText_d(g_optionTextParameter[i], g_temp_bgm_vol * 100);
				break;
			case(SE_VOLUME):
				SetText_d(g_optionTextParameter[i], g_temp_se_vol * 100);
				break;
			default:
				break;
			}
			

		}
	}

	//�^�C�g����ʁi�`���[�g���A���j
	else if (g_isTutorial) {		//�I������Ă��镶���̐F�ƃT�C�Y��ς���B
		for (int i = 0; i < TUTORIAL_MAX; i++) {
			g_tutorialTextParameter[i].color = TEXT_COLOR1;
			g_tutorialTextParameter[i].size = TUTORIAL_TEXT_SIZE1;
			g_tutorialTextParameter[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_POS_X, (float)(TUTORIAL_TEXT_POS_Y + (i * TUTORIAL_TEXT_POS_Y_PLUS)));
		}
		g_tutorialTextParameter[g_tutorialSelect].color = TEXT_COLOR2;
		g_tutorialTextParameter[g_tutorialSelect].size = TUTORIAL_TEXT_SIZE2;

		for (int i = 0; i < TUTORIAL_MAX; i++) {
			SetText(g_tutorialTextParameter[i], g_tutorialText[i]);
		}


		switch (g_tutorialSelect)
		{
		case KEYBOARD:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"���ǂ��c�v�`�r�c"},
				{"�_�b�V���c�r�g�h�e�s"},
				{"���Ă�c�₶�邵�L�[�����}�E�X"},
				{"���������c�P�����k�N���b�N"},
				{"���e�B�N���c�p�����q�N���b�N"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);
			}
			break;
		}
		case XBOX:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"���ǂ��c�k�X�e�B�b�N"},
				{"�_�b�V���c�k�R�{�^��"},
				{"���Ă�c�q�X�e�B�b�N"},
				{"���������c�k�a�{�^��"},
				{"���e�B�N���c�q�a�{�^��"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);
			}
			break;
		}
		case PS:
		{
			TEXT tutorialTextMainP[TUTORIAL_TEXT_MAIN];
			char tutorialTextMain[TUTORIAL_TEXT_MAIN][128] = {
				{"���ǂ��c�k�X�e�B�b�N"},
				{"�_�b�V���c�x�{�^��"},
				{"���Ă�c�q�X�e�B�b�N"},
				{"���������c�k�P�{�^��"},
				{"���e�B�N���c�q�P�{�^��"},
			};
			for (int i = 0; i < TUTORIAL_TEXT_MAIN; i++) {
				tutorialTextMainP[i].color = TEXT_COLOR2;
				tutorialTextMainP[i].size = TUTORIAL_TEXT_MAIN_SIZE1;
				tutorialTextMainP[i].pos = XMFLOAT2((float)TUTORIAL_TEXT_MAIN_POS_X, (float)(TUTORIAL_TEXT_MAIN_POS_Y + (i * TUTORIAL_TEXT_MAIN_POS_Y_PLUS)));
				SetText(tutorialTextMainP[i], tutorialTextMain[i]);
			}
			break;
		}
		default:
			break;
		}



	}

	//�^�C�g����ʁi���C���j
	else {
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

		TEXT text;
		text.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		text.pos = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130);
		text.size = 80;
		SetText(text, "�h�N�����������Q�[��");
	}

}