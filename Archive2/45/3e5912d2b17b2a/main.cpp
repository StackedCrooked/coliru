#include <stdio.h>
#include <unistd.h>

int main()
{
    int child_id = fork();
	setbuf(stdout, NULL);
	if(child_id == 0)
	{
		execlp("ls","ls", (char*) 0);
	}
	else
	{
		printf("parent process\n");
	}
	return 0;
}