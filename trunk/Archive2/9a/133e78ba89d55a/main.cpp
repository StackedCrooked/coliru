#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    fputwc(L'Æ', stdout);
    return 0;
}
