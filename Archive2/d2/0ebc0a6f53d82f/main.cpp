#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <boost/utility/string_ref.hpp> // optimization only

using namespace std;

static bool by_trailing_timestamp(std::string const& a, std::string const& b)
{
    assert(a.length()>=5);
    assert(b.length()>=5);

    return boost::string_ref(a).substr(a.length()-5)
        <  boost::string_ref(b).substr(b.length()-5);
}

int main()
{
    std::vector<std::string> trade, nbbo;

    {
        std::ifstream tradefile("trade.txt"), qfile("nbbo.txt");

        assert(tradefile && qfile);

        std::string line;
        while (std::getline(tradefile, line)) trade.push_back(line);
        while (std::getline(qfile, line))     nbbo.push_back(line);
    }

    // sort both
    std::sort(trade.begin(), trade.end(), by_trailing_timestamp);
    std::sort(nbbo.begin(),  nbbo.end(),  by_trailing_timestamp);

    // merge **and** print output
    std::merge(trade.begin(), trade.end(), nbbo.begin(), nbbo.end(), 
            std::ostream_iterator<std::string>(std::cout, "\n"), by_trailing_timestamp);
}
