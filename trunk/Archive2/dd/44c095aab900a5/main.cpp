#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>

static bool by_trailing_timestamp(std::string const& a, std::string const& b){
    assert(a.length()>=5  && b.length()>=5);
    return a.substr(a.length()-5) <  b.substr(b.length()-5);
}

int main() {
    std::vector<std::string> trade, nbbo;

    std::ifstream tradefile("trade.txt"), qfile("nbbo.txt");
    assert(tradefile && qfile);

    std::string line;
    while (std::getline(tradefile, line)) trade.push_back(line);
    while (std::getline(qfile, line))     nbbo.push_back(line);

    std::sort(trade.begin(), trade.end(), by_trailing_timestamp);
    std::sort(nbbo.begin(),  nbbo.end(),  by_trailing_timestamp);

    std::merge(trade.begin(), trade.end(), nbbo.begin(), nbbo.end(), 
            std::ostream_iterator<std::string>(std::cout, "\n"), by_trailing_timestamp);
}