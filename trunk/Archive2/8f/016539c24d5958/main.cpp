#include <stdio.h>
#include <unistd.h>

int main()
{
    int child_id = fork();
    if(child_id == 0)
    {
        execlp("sh", "sh", "-c", "ls", (char*) 0);
        printf("child process\n");
    }
    else
    {
        printf("parent process\n");
    }
    return 0;
}
