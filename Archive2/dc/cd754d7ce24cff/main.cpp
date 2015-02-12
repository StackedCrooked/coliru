#include <iostream>
#include "boost/filesystem.hpp"

int main(int argc, char *argv[])
{
    // list all files in current directory.
    //You could put any file path in here, e.g. "/home/me/mwah" to list that directory
    boost::filesystem::path p (".");
 
    boost::filesystem::directory_iterator end_itr;
 
    // cycle through the directory
    for (boost::filesystem::directory_iterator itr(p); itr !=end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) 
        {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();
            std::cout << current_file << std::endl;
        }
    }
}