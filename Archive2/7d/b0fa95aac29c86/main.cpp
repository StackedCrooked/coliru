#include <cstdio>
 
int main()
{
    std::printf("stdout is printed to console");
    std::freopen("redir.txt", "w", stdout);
    std::printf("stdout is redirected to a file");
    std::fclose(stdout);
}