#include <cstdlib>

int main()
{
    return system("find /usr/local/include/boost -type f -name \"*.hpp\" | xargs grep -i manager | head -n200");
}