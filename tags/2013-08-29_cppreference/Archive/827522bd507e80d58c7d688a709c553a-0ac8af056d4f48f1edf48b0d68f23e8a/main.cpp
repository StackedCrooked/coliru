#include <cstdlib>

int main()
{
    return system("find /usr/local/include -type f")
         + system("find /usr/local/bin -type f")
         + system("find /usr/include -type f")
         + system("find /usr/bin -type f");
}