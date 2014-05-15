#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>

int main()
{
    using namespace std::chrono ;
    const auto start = steady_clock::now() ;
    
    std::vector<std::string> file_list ; 
    
    auto begin = boost::filesystem::recursive_directory_iterator("/usr/local");
    const auto end = boost::filesystem::recursive_directory_iterator() ;
    unsigned long long cnt = 0 ;
    
    for( ; begin != end ; ++begin )
    {
        ++cnt ;
        const std::string path = begin->path().string() ;
        if( path.find( ".a" ) != std::string::npos ) file_list.push_back(path) ;
    }
    
    const auto dur = steady_clock::now() - start ;

    std::cout << cnt << " directory entries were searched\n" 
              << file_list.size() << " entries with '.a' in the path were added to the vector\n" 
              << "elapsed wall-clock time " << duration_cast<milliseconds>(dur).count() << " milliseconds.\n" ;
}
