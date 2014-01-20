#include <boost/filesystem.hpp>
#include <iostream>

void info( const boost::filesystem::path& relative_path )
{
    using namespace boost::filesystem ;

    std::cout << "rel path: " << relative_path << '\n' ;
    std::cout << "cwd: " << current_path() << '\n' ; // current working directory

    const path absolute_path = absolute(relative_path) ;
    std::cout << "absolute: " << absolute_path << '\n'
               << "root dir: " << absolute_path.root_directory() << '\n'
               << "root path: " << absolute_path.root_path() << '\n'
               << "parent dir: " << absolute_path.parent_path() << '\n'
               << "file name: " << absolute_path.filename() << '\n'
               << "-----------------------------------------------\n" ;
}

int main()
{

    info( "main.cpp" ) ; // relative path

    boost::filesystem::path data_dir = "data/out/text" ;
    boost::filesystem::create_directories(data_dir) ;

    info( data_dir / "result.txt" ) ; // relative path

    boost::filesystem::current_path(data_dir) ; // change cwd
    info( "result.txt" ) ; // relative path
}
