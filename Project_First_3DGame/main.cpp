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
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"CreateTheWorld"		// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);




//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_NAME;		// デバッグ文字表示用
//#endif

PLAY_MODE g_Mode = MODE_TITLE;

long g_MouseX = 0;
long g_MouseY = 0;

bool g_WindowActive = false;	//ウインドウがアクティブか

bool g_isClear = false;		//ゲームシーンでクリアしたか


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
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

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;



	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//OutputDebug("ウインドウの生成完了\n");




	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
//#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
//#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

//#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
//#endif


				//ウインドウがアクティブか判断
				HWND active_hWnd = GetActiveWindow();
				g_WindowActive = active_hWnd == hWnd;



				Update();			// 更新処理
				Draw();				// 描画処理

//#ifdef _DEBUG	// デバッグ版の時だけ表示する
				SetWindowText(hWnd, g_DebugStr);
//#endif


				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
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
// 共通の初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	InitInput(hInstance, hWnd);

	//レンダー
	InitRenderer(hInstance, hWnd, bWindow);

	//ライト
	InitLight();

	//text
	Init_text();

	//サウンドの初期化
	InitSound(hWnd);


	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void){

	UninitSound();

	Uninit_text();

	//レンダー
	UninitRenderer();


	UninitInput();

	
}

//=============================================================================
// 更新処理
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
// 描画処理
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
		DrawGameModel();	//RESULTで背景にゲーム画面を使いたいから
		DrawGame();
		DrawResult();
		break;
	case MODE_MAX:
		break;
	default:
		break;
	}

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(false);

	// ライティングを無効
	SetLightEnable(false);

	Draw_text();

	// ライティングを有効に
	SetLightEnable(true);	//TODO:ライト作ったらtrueに変える

	// Z比較あり
	SetDepthEnable(true);




	Present();
}



void SetMode(PLAY_MODE mode) {

	//MEMO:シーンごとの終了処理

	UninitTitle();
	UninitResult();

	StopSound();

	//MEMO:モードごとの初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		UninitGame();	//MEMO:リザルトの背景で使いたいからここで終了処理をする
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