#include "main.h"
#include "input_M.h"


static HWND g_hWnd;

HRESULT InitMinput(HWND hWnd) {
	g_hWnd = hWnd;

	ShowCursor(false);

	//カーソルをウインドウ上に拘束する
	WINDOWINFO WindowInfo;
	WindowInfo.cbSize = sizeof(WindowInfo);
	GetWindowInfo(hWnd, &WindowInfo);
	RECT clip;
	clip = WindowInfo.rcWindow;

	int x = clip.left + (SCREEN_WIDTH / 2);
	int y = clip.top + (SCREEN_HEIGHT / 2);
	//カーソルの固定（仮）

	SetCursorPos(x, y);

	return S_OK;
}