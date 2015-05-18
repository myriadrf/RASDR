

#ifdef EXPORT_DLL

#define CTR_6002DR2_LOGICDLL_EXPORTS

#ifdef CTR_6002DR2_LOGICDLL_EXPORTS
#define CTR_6002DR2_API __declspec(dllexport)
#else
#define CTR_6002DR2_API __declspec(dllimport)
#endif

#else
#define CTR_6002DR2_API
#endif


#ifdef WIN32
#define WIN32_LEAN_AND_MEAN


#include "windows.h"
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
#else
extern "C" CTR_6002DR2_API bool DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
#endif // WIN32
{
    return TRUE; // succesful
}
