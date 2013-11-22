#include <stdio.h>
 
int main()
{
    printf("stdout is printed to console");
    freopen("redir.txt", "w", stdout);
    printf("Stdout is redirected to a file");
    fclose(stdout);
}