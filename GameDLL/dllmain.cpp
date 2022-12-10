#include "dllmain.h"

#include <string>

//DLL�ǂݍ��ݎ��̎��s�i���������j
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){
#ifdef _DEBUG
    OutputDebugString("DLL�ǂݍ��ݐ���(����)\n");
#endif // _DEBUG

    return true;
}


//OutputDebugString��printf�݂����Ɏg���B
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




//XY��XYZ�̉�]�ɕϊ����ĉ��Z
DLLEXPOERT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}