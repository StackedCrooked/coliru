#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void sh(char *);
 
void sh( char  *cmd )
{
       int num;
       num = system(cmd);
}