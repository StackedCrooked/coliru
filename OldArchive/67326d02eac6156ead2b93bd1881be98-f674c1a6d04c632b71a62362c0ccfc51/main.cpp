#include <boost/filesystem.hpp>
#include <iostream>

int main ()
{
    boost::filesystem::path folder(boost::filesystem::current_path());
    for (boost::filesystem::directory_iterator it(folder), end; 
         it != end; ++it)
    {
        auto ext = it->path().extension();
        if (ext == ".jpeg")
        {
            std::cout << "is jpeg" << std::endl;
        }
    }
}