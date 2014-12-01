#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem ;

std::vector<std::string> files_in_directory( fs::path path = ".", bool recursive = true )
{
    std::vector<std::string> files ;

    try
    {
        if( fs::exists(path) ) files.push_back( fs::system_complete(path).string() ) ;
        
        if( fs::is_directory(path) )
        {
            using iterator = fs::directory_iterator ;
            for( iterator iter(path) ; iter != iterator() ; ++iter )
            {
                files.push_back( fs::system_complete( iter->path() ).string() ) ;
                if( recursive )
                {
                    for( const std::string& p : files_in_directory( iter->path() ) )
                        files.push_back( std::move(p) ) ;
                }
            }
        }
    }
    catch( const std::exception& ) { /* error */ }

    return files ;
}
int main()
{
    for( const std::string& path_str : files_in_directory( "/usr/local/share", true ) )
        std::cout << path_str << '\n' ;
}
