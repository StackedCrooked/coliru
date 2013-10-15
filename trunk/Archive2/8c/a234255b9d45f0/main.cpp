#include <stdio.h>
#include <string.h>

int
main (int argc, char **argv)
{
  char buf1[1000],buf2[1000],buf3[1000];

  char *p1 = stpcpy (buf1, (const char *) argv[0]); //this doesn't work
  printf ("buf1 = %s, p1 = %s\n", buf1, p1);

  stpcpy (buf2, (const char *) argv[0]); // this works
  printf ("buf2 = %s\n", buf2);

  char *p3 = stpcpy (buf3, (const char *) "123"); // this works too
  printf ("buf3 = %s, p3 = %s\n", buf3, p3);

  return 0;
}