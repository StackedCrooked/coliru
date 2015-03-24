#include <iostream>
#include <string>
#include <vector>

struct SubmoduleVersions
{
    int save;
    int program;
    int tool;
    int param;
};

SubmoduleVersions GetFileFormatSubmoduleVersion(int file_version)
{
    switch (file_version)
    {
       case 1:
         return SubmoduleVersions{1,2,3,4};
       default:
         return SubmoduleVersions{-1,-1,-1,-1};
    }
    
}

int main()
{
    auto versions = GetFileFormatSubmoduleVersion(1);
    
    std::cout << versions.save << std::endl;
}
