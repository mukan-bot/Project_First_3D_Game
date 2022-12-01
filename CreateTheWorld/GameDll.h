#pragma once


//GameDLLƒŠƒ“ƒN
#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/GameDLL.lib")
#else
#pragma comment (lib, "../x64/Release/GameDLL.lib")
#endif // _DEBUG

#define DLLINPORT extern "C" __declspec(dllimport) 

DLLINPORT void OutputDebug(const char* format, ...);