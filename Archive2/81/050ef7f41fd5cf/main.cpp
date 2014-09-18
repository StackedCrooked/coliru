#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "");
    fputwc(L'Æ', stdout);
    return 0;
}
