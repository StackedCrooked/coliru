#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

fs::path remove_current_dir(const fs::path & path)
{
    fs::path ret;
    
    for (const auto & segment : path)
    {
        if (segment != ".")
        {
            ret /= segment;
        }
    }
    
    return ret;
}

int main()
{
    for (fs::directory_iterator it{ "." }; it != fs::directory_iterator{}; ++it)
    {
        std::cout << remove_current_dir(it->path()) << std::endl;
    }
}
