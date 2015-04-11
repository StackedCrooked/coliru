#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdexcept>

int user_count = 0;

//Holy smokes this entire thing is so UGLY!
void parse(std::string line, std::vector<std::pair<std::string, float> >& user_times)
{
    //Find the colon
    std::size_t colon_pos = line.find(':');
    
    if (colon_pos == std::string::npos)
        throw std::invalid_argument("Could not find a :");
    
    std::string user;

    //Copy until right before colon
    for (std::size_t i = 0; i < colon_pos; ++i)
    {
        user += line.at(i);
    }
    
    //Trim everything to colon, including colon
    line.erase(0, colon_pos+1);
    
    //Get the time as a float
    float time = std::atof(line.c_str());
    
    //Create new float, add to list
    if (time <= 60.00f)
    {
        user_times.push_back(std::pair<std::string, float>(user, time));
    } else if (time < 0.00f) {
        throw std::invalid_argument("Time value is negative");
    } else
        throw std::invalid_argument("Time value is over 60.00 seconds");

    
}

int main ()
{
    std::ifstream file;
    file.open("input.txt");
    
    //Store names
    std::vector<std::pair<std::string, float> > user_times;
    
    //buffer
    std::string buffer;
    
    char c;
    int line_no = 1;
    
    while(file >> std::noskipws >> c && !std::isalpha(c))
    {
        if (c == '\n')

            ++line_no;
    }
    
    file.putback(c);
    

    while (std::getline(file,buffer)) {
        try {
            parse(buffer, user_times);
        }
        catch(std::exception& e) {
            std::cout << "Error on line " << line_no << ": " << e.what() << std::endl;
        }
        
        ++line_no;
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
    
    file.close();
    
    std::ofstream output;
    output.open("output.txt");
    
    for (auto it : user_times)
    {
        output << it.first << ": " << (int)std::floor(it.second) << std::endl;
    }
    
    output.close();
}
