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



DLLEXPOERT int xmlParse(char* sorce, char* tag, char* data){
    char tagStart[64];
    char tagEnd[64];
    int dataLen;
    sprintf_s(tagStart, "<%s>", tag);
    sprintf_s(tagEnd, "</%s>", tag);
    

    /////変数初期化完了
    //データの長さを計算
    dataLen = strlen(strstr(sorce, tagStart) + strlen(tagStart)) - strlen(strstr(sorce, tagEnd));


    memset(data, '\0', strlen(sorce) + 1); //ソースと同じ長さに/0を入れておく
    memcpy(data, strstr(sorce, tagStart) + strlen(tagStart), dataLen);


#ifdef _DEBUG
    OutputDebug(data);
#endif // _DEBUG

    return 0;
}