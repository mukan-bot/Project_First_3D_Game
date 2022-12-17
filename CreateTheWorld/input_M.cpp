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


	//カーソルをウインドウ上に拘束する
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