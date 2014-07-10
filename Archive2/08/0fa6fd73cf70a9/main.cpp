#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

int main()
{
    using namespace boost;
    std::istream& rgxFile = std::cin; // ("regex.txt", ios::in);
    std::ifstream input("input.txt");

    std::string line, text;
    while (getline(input, text))
    {
        while(getline(rgxFile, line))
        {    
            smatch what;
            regex exp(line);
            if (regex_search(text, what, exp))
            {
                std::cout << "destination IP: " << what["destination_ip"] << " ";
            } else
            {
                std::cout<<"Nothing Found.\n";
            }
        }   
    }   
}
