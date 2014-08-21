#include <boost/filesystem.hpp>
#include <iostream>

int main() {
    std::string directory_path_string = "/var";
    boost::filesystem::path dir(directory_path_string);
    
    if (boost::filesystem::is_directory(dir) && boost::filesystem::exists(dir))
    {
        std::cout << "it does.";
    }
}