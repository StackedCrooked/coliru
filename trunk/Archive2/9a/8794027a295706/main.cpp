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
       case 2:
         return SubmoduleVersions{2,2,3,4};
       default:
         return SubmoduleVersions{-1,-1,-1,-1};
    }
    
}

int main()
{
    auto versions = GetFileFormatSubmoduleVersion(1);
    std::cout << versions.save << std::endl;
    
    // alternative
    auto save_version = GetFileFormatSubmoduleVersion(1).save;
    std::cout << save_version << std::endl;

}
