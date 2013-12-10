#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
 
int main()
{
    for(int i = 0; ; ++i)
    {
        fprintf(stderr, "%d\n", i);
    }
}