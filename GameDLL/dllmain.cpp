#include "dllmain.h"

#include <string>

//DLL読み込み時の実行（初期処理）
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){
#ifdef _DEBUG
    OutputDebugString("DLL読み込み成功(多分)\n");
#endif // _DEBUG

    return true;
}


//OutputDebugStringをprintfみたいに使う。
DLLEXPOERT void OutputDebug(const char* format, ...) {
#ifdef _DEBUG

    char szBufDebug[4096] = "";

    va_list arg;

    va_start(arg, format);
    vsprintf_s(szBufDebug, format, arg);
    va_end(arg);

    OutputDebugString(szBufDebug);

#endif // DEBUG
}


