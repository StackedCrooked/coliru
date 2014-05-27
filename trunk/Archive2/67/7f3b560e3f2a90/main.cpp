#include <stdio.h>

typedef const char  *PCSTR, *LPCSTR; 
typedef char        *PSTR, *LPSTR;
typedef const wchar_t   *LPCWSTR, *PCWSTR;
typedef wchar_t     *LPWSTR, *PWSTR;

typedef LPCSTR      PCTSTR, LPCTSTR; // expected unqualified-id before ‘const’
typedef PSTR        PTSTR, LPTSTR; //expected unqualified-id before ‘char’
typedef char        TCHAR; //   multiple types in one declaration
typedef char*       PTCHAR;

int main() {

  return 0;
}