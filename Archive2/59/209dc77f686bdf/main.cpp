#include <cstddef>

using LPCTSTR = const char *;
using DWORD = unsigned int;

DWORD GetPrivateProfileStringA(LPCTSTR, LPCTSTR, void *, char *, DWORD, LPCTSTR);


LPCTSTR getConfigValue(LPCTSTR key) {
    char retval[256];

    DWORD dw;
    if ((dw = GetPrivateProfileStringA("RLWELF", "DestinationIP", NULL, retval, 256, ".\\rlwelf.ini")) > 0) {    
        return NULL;
    }

//    OutputDebugStringA(retval);

    return (LPCTSTR)retval;
}