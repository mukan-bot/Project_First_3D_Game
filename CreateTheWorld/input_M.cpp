#include "main.h"
#include "input_M.h"


static HWND g_hWnd;

HRESULT InitMinput(HWND hWnd) {
	g_hWnd = hWnd;

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