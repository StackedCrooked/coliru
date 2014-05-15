#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <boost/filesystem.hpp>
#include <atomic>
#include <future>

std::atomic<unsigned int> nthreads{1} ;

std::vector<std::string> find_files( boost::filesystem::path p, std::string substr )
{
    ++nthreads ;
    std::vector<std::string> file_list ;
    
    auto begin = boost::filesystem::recursive_directory_iterator(p);
    const auto end = boost::filesystem::recursive_directory_iterator() ;

    for( ; begin != end ; ++begin )
    {
        const std::string path = begin->path().string() ;
        if( path.find( substr ) != std::string::npos ) file_list.push_back(path) ;
    }
    
    return file_list ;
}

int main()
{
    using namespace std::chrono ;
    const auto start = steady_clock::now() ;
    
    std::vector<std::string> file_list ; 
    
    auto begin = boost::filesystem::directory_iterator("/usr/local");
    const auto end = boost::filesystem::directory_iterator() ;
    
    std::vector< std::future< std::vector<std::string> > > futures ;
    for( ; begin != end ; ++begin ) 
    {
        const boost::filesystem::path p = begin->path() ;
        if( boost::filesystem::is_directory(p) ) 
           futures.emplace_back( std::async( std::launch::async, find_files, p, ".a" ) ) ;
        else
        {
            const std::string path_str = p.string() ;
            if( path_str.find( ".a" ) != std::string::npos ) file_list.push_back(path_str) ;
        }
    }
    
    for( auto& f : futures ) 
    {
        auto v = f.get() ;
        file_list.insert( file_list.end(), v.begin(), v.end() ) ;
    }
    
    const auto dur = steady_clock::now() - start ;

    std::cout << file_list.size() << " entries with '.a' in the path were added to the vector\n" 
              << "elapsed wall-clock time " << duration_cast<milliseconds>(dur).count() << " milliseconds.\n" 
              << "#threads: " << nthreads << '\n' ;
}
