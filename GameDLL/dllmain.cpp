//=============================================================================
//
// Author : TakeuchiHiroto
//
//=============================================================================
#include "dllmain.h"

#include <string>

//DLL“Ç‚Ýž‚ÝŽž‚ÌŽÀsi‰Šúˆ—j
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){
#ifdef _DEBUG
    OutputDebugString("DLL“Ç‚Ýž‚Ý¬Œ÷(‘½•ª)\n");
#endif // _DEBUG

    return true;
}


//OutputDebugString‚ðprintf‚Ý‚½‚¢‚ÉŽg‚¤B
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




//XY‚ðXYZ‚Ì‰ñ“]‚É•ÏŠ·‚µ‚Ä‰ÁŽZ
DLLEXPOERT void DllRotation(XMFLOAT2 move, XMFLOAT3* rotation, float offset = 0.003f) {
    rotation->x += (float)(move.x) * offset;
    rotation->z += (float)(move.y) * offset;
}

//XMFLOAT3“¯Žm‚Ì‘«‚µŽZ
DLLEXPOERT XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z); 
}
//XMFLOAT3“¯Žm‚Ìˆø‚«ŽZ
DLLEXPOERT XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) { 
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z); 
}
//XMFLOAT3“¯Žm‚ÌŠ|‚¯ŽZ
DLLEXPOERT XMFLOAT3 MulXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z); 
}
//XMFLOAT3“¯Žm‚ÌŠ„‚èŽZ
DLLEXPOERT XMFLOAT3 DivXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
    return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z); 
}
