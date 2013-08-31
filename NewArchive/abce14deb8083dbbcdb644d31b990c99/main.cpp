#include <cstdlib>

int main()
{
    return system("find /usr/local/include -name \"*\.hpp\" | xargs grep -i manager | head -n1001");
}