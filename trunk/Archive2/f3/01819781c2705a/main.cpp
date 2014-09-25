#include <iostream>
#include <vector>
#include <unistd.h>

void foo()
{
    std::vector<std::vector<unsigned int>> voxelToPixel(1<<27);

    for (unsigned int idx=0; idx < voxelToPixel.size(); idx++)
        voxelToPixel[idx].push_back(idx);
}

int main()
{
    foo();
    std::cout << "End" << std::endl;
    sleep(30);
    return 0;
}