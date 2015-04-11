#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

int user_count = 0;

void parse(std::string line, std::vector<std::pair<std::string, float> >& user_times)
{
    std::size_t colon_pos = line.find(':');
    
    std::string user;

    for (std::size_t i = 0; i < colon_pos; ++i)
    {
        user += line.at(i);
    }
    
    line.erase(0, colon_pos+1);
    
    float time = std::atof(line.c_str());
    
    if (time < 60.00f)
    {
        user_times.push_back(std::pair<std::string, float>(user, time));
    }
    
    
}

int main ()
{
    std::ifstream file;
    file.open("input.txt");
    
    //Store names
    std::vector<std::pair<std::string, float> > user_times;
    
    //buffer
    std::string buffer;
    
    std::getline(file, buffer);
    user_count = std::atoi(buffer.c_str());
    
    while (std::getline(file,buffer) && user_count != 0) {
        parse(buffer, user_times);
        --user_count;
    }
    
    std::sort(user_times.rbegin(), user_times.rend(),
    
    [&](std::pair<std::string, float> i, std::pair<std::string, float> j) {
        return (i.second < j.second);
    }
    
    );
    
    for (auto it : user_times)
    {
        std::cout << it.first << ": " << (int)std::floor(it.second) << std::endl;
    }
}