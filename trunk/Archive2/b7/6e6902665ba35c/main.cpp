#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    wprintf(L"<cyanboy> why can't C treat my national pride as characters?\n\
<cyanboy> Æ Æ Å\n\
<cyanboy> ÆØÅ\n\
<cyanboy> øæå\n", stdout);
    return 0;
}
