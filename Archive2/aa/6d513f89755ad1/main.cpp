#define _GNU_SOURCE
#define max_buff 1000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void strip_crlf(char* s)
{
    char* p = strpbrk (s, "\r\n");
    if (p) *p = '\0';
}

int main(int argc, char** argv) // C requires these parameters
{
  char fname[max_buff];
  char lname[max_buff];

  printf("Enter the line of text you are searching for ");

  fgets(fname,max_buff,stdin);
  strip_crlf(fname);
  
  printf("Enter the search term ");

  fgets(lname,max_buff,stdin);
  strip_crlf(lname);

  char *answer = strcasestr(fname,lname);
  if (!answer) {
    puts("not found");
  }
  else {
    puts(answer);
  }
}
