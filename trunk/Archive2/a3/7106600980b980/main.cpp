#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
  setlocale(LC_ALL, "en_US.UTF-8");
  FILE* fp = fopen("/tmp/wc.test", "w+");
  long ftell_out;

  printf ("fputwc: %d\n", (int)fputwc('1', fp));

  printf ("ftell 1: %d\n", (int)(ftell_out = ftell(fp)));

  printf ("fputwc: %d\n", (int)fputwc('2', fp));

  printf ("fseek 1: %d\n", fseek(fp, ftell_out, SEEK_SET));
  printf ("ftell 2: %d\n", (int)(ftell_out = ftell(fp)));

  printf ("fputwc: %d\n", (int)fputwc('3', fp));

  fclose(fp);
  return 0;
}
