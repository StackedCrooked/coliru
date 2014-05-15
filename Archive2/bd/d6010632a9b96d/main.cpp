#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <boost/filesystem.hpp>

struct StructA {
    boost::filesystem::path mPath;
    std::string elem1;
    int intVal;
};

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
operator<<(std::basic_ostream<CharT, Traits>& os, StructA const& sa) {
    return os << sa.mPath << " - " << sa.elem1 << " - " << sa.intVal << std::endl;
}


int main()
{
    std::vector<StructA> aStructs = {
        {"/zoo/dir1/filename.txt", "nameA1", 1}, 
        {"/fad/dir1/filename.txt", "nameA1", 4}, 
        {"/tmp/dir1/filename.txt", "nameA1", 3}
    };    
    
    std::cout << "Order[mPath.filename(), elem1, intVal]" << std::endl;
    std::cout << "======================================" << std::endl;
    std::sort(aStructs.begin(), aStructs.end(),
        [](const StructA& lhs, const StructA& rhs){
            return std::make_tuple(lhs.mPath.filename(), lhs.elem1, lhs.intVal) < 
                std::make_tuple(rhs.mPath.filename(), rhs.elem1, rhs.intVal);
        });
        
    // print reordered structs
    std::copy(aStructs.begin(), aStructs.end(),
        std::ostream_iterator<StructA>(std::cout, ""));        
        
    std::cout << std::endl;
    
    std::cout << "Order[mPath, elem1, intVal]" << std::endl;
    std::cout << "======================================" << std::endl;
    std::sort(aStructs.begin(), aStructs.end(),
        [](const StructA& lhs, const StructA& rhs){
            return std::tie(lhs.mPath, lhs.elem1, lhs.intVal) < 
                std::tie(rhs.mPath, rhs.elem1, rhs.intVal);
        });
        
    // print reordered structs
    std::copy(aStructs.begin(), aStructs.end(),
        std::ostream_iterator<StructA>(std::cout, ""));

    std::cout << std::endl;
    
    std::cout << "Order[mPath.filename(), elem1, intVal]" << std::endl;
    std::cout << "======================================" << std::endl;
    std::sort(aStructs.begin(), aStructs.end(),
        [](const StructA& lhs, const StructA& rhs){
            // attempt at efficiency - but not quite right
            // AHA, I think I figured it out, 
            // std::get<0>(lhs) < std::get<0>(rhs)) || (!(bool)(std::get<0>(rhs) < std::get<0>(lhs))
            return ((lhs.mPath.filename() < rhs.mPath.filename()) || 
                    !(rhs.mPath.filename() < lhs.mPath.filename())) && 
                std::tie(lhs.elem1, lhs.intVal) < std::tie(rhs.elem1, rhs.intVal);
        });
        
    // print reordered structs
    std::copy(aStructs.begin(), aStructs.end(),
        std::ostream_iterator<StructA>(std::cout, ""));
}
