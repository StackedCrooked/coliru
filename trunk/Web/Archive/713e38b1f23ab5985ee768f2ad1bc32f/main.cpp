#include <cstdlib>

int main()
{
    return system("find /usr/local/include/boost | xargs -I {} grep -i manager {} | grep -i manager");
}