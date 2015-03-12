#include <unistd.h>
#include <string.h>
int szstart()
{
    char* msg = "No main here\n";
    write(1, msg, strlen(msg));
    _exit(0);
}
