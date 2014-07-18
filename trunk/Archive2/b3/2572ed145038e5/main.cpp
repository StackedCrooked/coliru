#include <iostream>
#include <sstream>

#include <fstream>
#include <vector>

#include <dirent.h>

void listDir(const std::string & dirString, int recurse)
{
    DIR * dir = opendir(dirString.c_str());
    dirent * entry;
    while((entry = readdir(dir)) != nullptr)
    {
        std::string file(entry->d_name);
        std::cout << dirString << "/" << file << std::endl;
        
        if(entry->d_type == DT_DIR && file != "." && file != ".." && recurse)
        {   
            listDir(dirString + "/" + file, recurse - 1);
        }
    }
}

std::vector<std::string> searchFile(const std::string & dirString,
                                    const std::string & fileName)
{
    std::vector<std::string> files;
    
    DIR * dir = opendir(dirString.c_str());
    dirent * entry;
    while((entry = readdir(dir)) != nullptr)
    {
        std::string file(entry->d_name);
        if(file == fileName)
        {
            files.push_back(dirString + "/" + file);
        }
        
        if(entry->d_type == DT_DIR && file != "." && file != "..")
        {   
            std::vector<std::string> subFiles = searchFile(dirString + "/" + file, fileName);
            for(auto & subFile : subFiles)
            {
                files.push_back(subFile);
            }
        }
    }
    
    return files;
}

int main()
{
    for(auto & file : searchFile("/tmp", "main.cpp"))
    {
        std::ifstream i(file);
        
        if(!i)
        {
            std::cout << "error opening file" << std::endl;
            continue;
        }
        
        std::string line;
        while(getline(i, line))
        {
            std::cout << line << std::endl;
        }
    }
    
    return 0;
}