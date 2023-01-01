//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "main.h"
#include "input_M.h"

static HWND g_hWnd;
static long g_mousePos_X, g_mousePos_Y;	//いちフレまえの情報の保存
static long g_mouseVec_X, g_mouseVec_Y;	//計算結果の保存
bool g_cursorMove = true;

HRESULT InitMinput(HWND hWnd) {
	g_hWnd = hWnd;

	//マウスカーソルを非表示にする
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


void UpdateMinput(void) {

	POINT po;

	GetCursorPos(&po);

	g_mouseVec_X = po.x - g_mousePos_X;
	g_mouseVec_Y = po.y - g_mousePos_Y;

	if (!g_cursorMove) {

		//カーソルをウインドウ上に拘束する
		WINDOWINFO WindowInfo;
		WindowInfo.cbSize = sizeof(WindowInfo);
		GetWindowInfo(g_hWnd, &WindowInfo);
		RECT clip;
		clip = WindowInfo.rcWindow;

		int x = clip.left + (SCREEN_WIDTH / 2);
		int y = clip.top + (SCREEN_HEIGHT / 2);

		//画面外に出るとカーソルがチラチラするので画面からでないようにする。
		ClipCursor(&clip);

		//カーソルを真ん中に固定する
		SetCursorPos(x, y);

	}





	GetCursorPos(&po);

	g_mousePos_X = po.x;
	g_mousePos_Y = po.y;
}


XMFLOAT2 GetMouseVec(void) {
	XMFLOAT2 ans;

	ans.x = (float)g_mouseVec_X;
	ans.y = (float)g_mouseVec_Y;

	return ans;
}

XMFLOAT2 GetMousePos(void) {
	XMFLOAT2 ans;

	ans.x = (float)g_mousePos_X;
	ans.y = (float)g_mousePos_Y;

	return ans;
}

void SetCursorMove(bool is) {
	g_cursorMove = is;
	ShowCursor(is);	//MEMO:カーソルが固定されているときはカーソルを非表示にする
}