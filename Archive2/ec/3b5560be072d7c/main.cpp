#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}

struct HeaderStruct
{
    int mSetupCmd;
    int mCleanupCmd;
    int mGetCmd;
    int mPutCmd;
    std::string mFileName;

    HeaderStruct(int setupCmd, int cleanupCmd, int getCmd, int putCmd, const std::string& rFileName) 
        : mSetupCmd(setupCmd)
        , mCleanupCmd(cleanupCmd)
        , mGetCmd(getCmd)
        , mPutCmd(putCmd)
        , mFileName(rFileName) 
    {}

    // let stream operators be friend functions instead of members!
    inline friend std::ostream& operator << (std::ostream& os, const HeaderStruct& rVal) {
        os << "getCmd[" << rVal.mGetCmd << "], fileName['" << rVal.mFileName << "']";
        return os;
    }

    // @JC change to std::tuple or custom lambda
    bool operator < (const HeaderStruct& rVal) const {
        return (mGetCmd > rVal.mGetCmd);
    }
};


int main()
{    
    std::vector <HeaderStruct> testVec = {
        HeaderStruct(1, 2, 4, 0, "file1_cmd4._hr"),
        HeaderStruct(1, 2, 4, 0, "file2_cmd4._hr"),
        HeaderStruct(1, 2, 4, 0, "file3_cmd4._hr"),
        HeaderStruct(1, 2, 3, 0, "file1_cmd3._hr"),
        HeaderStruct(1, 2, 3, 0, "file2_cmd3._hr"),
        HeaderStruct(1, 2, 9, 0, "file1_cmd9._hr"),
        HeaderStruct(1, 2, 9, 0, "file2_cmd9._hr"),
        HeaderStruct(1, 2, 9, 0, "file3_cmd9._hr"),
        HeaderStruct(1, 2, 9, 0, "file4_cmd9._hr"),
        HeaderStruct(1, 2, 7, 0, "file1_cmd7._hr"), 
        HeaderStruct(1, 2, 7, 0, "file2_cmd7._hr"), 
        HeaderStruct(1, 2, 6, 0, "file1_cmd6._hr")
    };
    
    // target data type orderd according to a key - 
    // in this case a read command index
    std::multimap<int, HeaderStruct> tempMap;

    std::transform (testVec.cbegin(), testVec.cend(), 
        std::inserter (tempMap, tempMap.begin()),
        [](const HeaderStruct& rHeaderStruct){
            // this is where we can tweak the multimap ordering
            return std::make_pair(
                rHeaderStruct.mGetCmd, rHeaderStruct);
        });
        
    // use transformation to transform from vector to multimap
    // much simpler than specialization of the std::copy algorithm
    std::cout << "transform vector => multimap" <<std::endl;
    std::cout << "============================\n" << std::endl;
    std::cout << "multimap size:" << tempMap.size() << std::endl;
    std::cout << "multimap contents:"  << std::endl;
    std::cout << "==================" << std::endl;
    std::for_each(tempMap.cbegin(), tempMap.cend(), 
        [](const std::multimap<int, HeaderStruct>::value_type& rValue){
            std::cout 
            << "key[" << rValue.first 
            << "] value:" << rValue.second.mFileName 
            << std::endl;
        });
    
    std::cout << std::endl;
    
    for (auto iter = tempMap.cbegin(); iter != tempMap.cend(); ) {
        // this is where the magic happens! range.first points
        // to the first value with iter->first as the key
        // while range.second points 1 beyond it - up to end()
        auto range = tempMap.equal_range(iter->first);
        std::cout << "processing [" 
            << std::distance (range.first, range.second) 
            << "] entries with GetFileCmd[" << range.first->first 
            << "]" << std::endl;
        std::for_each(range.first, range.second, 
            [](const std::multimap<int, HeaderStruct>::value_type& rValue){
                std::cout 
                << "transferList::addFile(" 
                << rValue.second.mFileName << ")" <<  std::endl;
            });
        std::cout << std::endl;
        // advance to the next range
        iter = range.second;
    }    
    return 0;
}
