#include <iostream>
#include <iterator>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

int main()
{
    std::vector<std::string> file_list ; 
    
    auto end = recursive_directory_iterator() ;
    for( auto begin = recursive_directory_iterator("/usr/local") ; begin != end ; ++begin )
    {
        const auto& de = *begin ;
    }
}
