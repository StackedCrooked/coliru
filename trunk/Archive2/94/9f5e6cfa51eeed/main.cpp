#include <string>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>

struct HeaderFile {    
    boost::filesystem::path mHeaderPath;
    int nSetupCmd;
    int nFileGetCmd;
    int nFilePutCmd;
    
    // Compiler supplies copy-constructor and assignment operator.
    inline bool operator<(const HeaderFile& rhs) const {
        return std::tie(nSetupCmd, nFileGetCmd) < 
            std::tie(rhs.nSetupCmd, rhs.nFileGetCmd);
    }    
};

std::ostream& 
operator<<(std::ostream& os, const HeaderFile& hr)
{
    os  << "path[" << hr.mHeaderPath 
        << "] nSetupCmd[" <<  hr.nSetupCmd 
        << "] nFileGetCmd[" <<  hr.nFileGetCmd
        << "] nFilePutCmd[" <<  hr.nFilePutCmd << "]";
    return os;
    
}

int main()
{
    // initially unsorted list of StructA
    std::vector<HeaderFile> headerFiles = {
        {"filename1._hr", 1, 6, 6}, 
        {"filename2._hr", 3, 6, 6}, 
        {"filename3._hr", 3, 6, 6}, 
        {"filename4._hr", 2, 6, 6}, 
        {"filename5._hr", 1, 6, 6}, 
        {"filename6._hr", 3, 7, 7}
    };
    
    std::cout << "unsorted header files" << std::endl;
    std::copy(headerFiles.begin(), headerFiles.end(), 
        std::ostream_iterator<HeaderFile>(std::cout, "\n"));    
    
    // sort using operator < - which in turn uses nSetupCmd 
    // as primary ordering and nFileGetCmd as secondray
    std::sort(headerFiles.begin(), headerFiles.end()); 
    
    std::cout << "header files (using nFileGetCmd, nFileGetCmd)" << std::endl;
    std::copy(headerFiles.begin(), headerFiles.end(), 
        std::ostream_iterator<HeaderFile>(std::cout, "\n"));    
}
