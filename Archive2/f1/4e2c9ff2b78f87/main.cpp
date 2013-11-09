#include <cstdlib>
#include <iostream>

int main()
{
    const size_t gb = 1024 * 1024 * 1024;
    void *allocs[1000] = {0};
    int i;
    for (i = 0; i < 1000; i++)
    {
        allocs[i] = malloc(gb);
        std::cout << allocs[i] << '\n';
    }
    std::cout << "Allocated 1000 gb of memory\n";
}
