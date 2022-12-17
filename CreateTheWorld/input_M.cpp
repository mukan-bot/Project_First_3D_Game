//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input_M.h"

static HWND g_hWnd;
static long g_mousePos_X, g_mousePos_Y;	//�����t���܂��̏��̕ۑ�
static long g_mouseVec_X, g_mouseVec_Y;	//�v�Z���ʂ̕ۑ�


HRESULT InitMinput(HWND hWnd) {
	g_hWnd = hWnd;

	//�}�E�X�J�[�\�����\���ɂ���
	ShowCursor(false);

	//�J�[�\�����E�C���h�E��ɍS������
	WINDOWINFO WindowInfo;
	WindowInfo.cbSize = sizeof(WindowInfo);
	GetWindowInfo(hWnd, &WindowInfo);
	RECT clip;
	clip = WindowInfo.rcWindow;

	int x = clip.left + (SCREEN_WIDTH / 2);
	int y = clip.top + (SCREEN_HEIGHT / 2);
	//�J�[�\���̌Œ�i���j

	SetCursorPos(x, y);

	return S_OK;
}


void UpdateMinput(void) {

	POINT po;

	GetCursorPos(&po);

	g_mouseVec_X = po.x - g_mousePos_X;
	g_mouseVec_Y = po.y - g_mousePos_Y;


	//�J�[�\�����E�C���h�E��ɍS������
	WINDOWINFO WindowInfo;
	WindowInfo.cbSize = sizeof(WindowInfo);
	GetWindowInfo(g_hWnd, &WindowInfo);
	RECT clip;
	clip = WindowInfo.rcWindow;

	int x = clip.left + (SCREEN_WIDTH / 2);
	int y = clip.top + (SCREEN_HEIGHT / 2);


	SetCursorPos(x, y);


	GetCursorPos(&po);

	g_mousePos_X = po.x;
	g_mousePos_Y = po.y;

	//g_mousePos_X = GetMousePosX();
	//g_mousePos_Y = GetMousePosY();





}


XMFLOAT2 GetMouseVec(void) {
	XMFLOAT2 ans;
	ans.x = (float)g_mouseVec_X;
	ans.y = (float)g_mouseVec_Y;

	OutputDebug("X:%f   Y:%f\n", ans.x,ans.y);
	return ans;
}