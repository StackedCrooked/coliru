#include <iostream>
#include <string>
#include <vector>

struct StructA {
    std::string mLongName;
    std::string mShortName;
    inline friend std::ostream& operator << (std::ostream& os, const StructA& rStruct) {
        // I dont know how to use a generic verbose flag - so use this - very bad idea 
        // but perhaps the stackoverflow people can help out with a good suggestion
        if (os.flags() & os.skipws) {
            os << rStruct.mShortName << std::endl;
        } else {
            os << rStruct.mLongName << std::endl;
        }
        return os;
    }
};

int main()
{
    StructA test {"Verbose Name", "Short Name"};
    std::cout << test  << std::noskipws << test << test << std::skipws << test;
}
