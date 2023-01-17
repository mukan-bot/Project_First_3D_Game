//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "input_M.h"
#include "camera.h"
#include "GameObject.h"
#include "GameModel.h"
#include "text.h"
#include "light.h"
#include "sound.h"

#include "M_title.h"
#include "M_game.h"
#include "M_result.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"CreateTheWorld"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);




//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_NAME;		// �f�o�b�O�����\���p
//#endif

PLAY_MODE g_Mode = MODE_TITLE;

long g_MouseX = 0;
long g_MouseY = 0;

bool g_WindowActive = false;	//�E�C���h�E���A�N�e�B�u��

bool g_isClear = false;		//�Q�[���V�[���ŃN���A������


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;



	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//OutputDebug("�E�C���h�E�̐�������\n");




	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
//#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
//#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

//#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
//#endif


				//�E�C���h�E���A�N�e�B�u�����f
				HWND active_hWnd = GetActiveWindow();
				g_WindowActive = active_hWnd == hWnd;



				Update();			// �X�V����
				Draw();				// �`�揈��

//#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
				SetWindowText(hWnd, g_DebugStr);
//#endif


				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ���ʂ̏���������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	InitInput(hInstance, hWnd);

	//�����_�[
	InitRenderer(hInstance, hWnd, bWindow);

	//���C�g
	InitLight();

	//text
	Init_text();

	//�T�E���h�̏�����
	InitSound(hWnd);


	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void){

	UninitSound();

	Uninit_text();

	//�����_�[
	UninitRenderer();


	UninitInput();

	
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void){


	UpdateInput();


	UpdateCamera();

	
	switch (g_Mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_GAME:
		UpdateGame();
		UpdateGameObject();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_MAX:
		break;
	default:
		break;
	}

	UpdateLight();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void){
	Clear();
	DrawCamera();

	switch (g_Mode)
	{
	case MODE_TITLE:
		DrawTitle();
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_GAME:
		DrawGameModel();
		DrawGame();
		break;
	case MODE_RESULT:
		DrawGameModel();	//RESULT�Ŕw�i�ɃQ�[����ʂ��g����������
		DrawGame();
		DrawResult();
		break;
	case MODE_MAX:
		break;
	default:
		break;
	}

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
}



void SetMode(PLAY_MODE mode) {

	//MEMO:�V�[�����Ƃ̏I������

	UninitTitle();
	UninitResult();

	StopSound();

	//MEMO:���[�h���Ƃ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		UninitGame();	//MEMO:���U���g�̔w�i�Ŏg���������炱���ŏI������������
		InitTitle();
		SetCursorMove(true);
		ShowCursor(true);
		PlaySound(SOUND_LABEL_BGM_title);
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_GAME:
		PlaySound(SOUND_LABEL_BGM_game);
		InitGame();
		ShowCursor(false);
		SetCursorMove(false);
		ShowCursor(false);
		break;
	case MODE_RESULT:
		if (GetIsClear) {
			PlaySound(SOUND_LABEL_BGM_result_kati);
		}
		else {
			PlaySound(SOUND_LABEL_BGM_result_make);
		}
		InitResult();
		SetCursorMove(true);
		ShowCursor(true);
		break;
	case MODE_MAX:
		break;
	default:
		break;
	}

	g_Mode = mode;
}

PLAY_MODE GetMode(void) {
	return g_Mode;
}


bool GetWindowActive(void) {
	return g_WindowActive;
}

bool GetIsClear(void) {
	return g_isClear;
}

void SetIsClear(bool is) {
	g_isClear = is;
}