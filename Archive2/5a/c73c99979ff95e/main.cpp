#include <cstdio>
#include <cwchar>

using namespace std;

int main ()
{
    wchar_t  ws[100];
    swprintf(ws, 100, L"%s", "ansi string");
    wprintf(L"%ls\n", ws);
    return 0;
}