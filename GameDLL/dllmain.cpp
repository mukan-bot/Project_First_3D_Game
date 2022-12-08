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



DLLEXPOERT int xmlParse(char* sorce, char* tag, char* data){
    char tagStart[64];
    char tagEnd[64];
    int dataLen;
    sprintf_s(tagStart, "<%s>", tag);
    sprintf_s(tagEnd, "</%s>", tag);
    

    /////�ϐ�����������
    //�f�[�^�̒������v�Z
    dataLen = strlen(strstr(sorce, tagStart) + strlen(tagStart)) - strlen(strstr(sorce, tagEnd));


    memset(data, '\0', strlen(sorce) + 1); //�\�[�X�Ɠ���������/0�����Ă���
    memcpy(data, strstr(sorce, tagStart) + strlen(tagStart), dataLen);


#ifdef _DEBUG
    OutputDebug(data);
#endif // _DEBUG

    return 0;
}