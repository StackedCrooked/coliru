#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <boost/random.hpp>

int main()
{  
    boost::mt19937 e2;
    boost::normal_distribution<> dist(70, 10);
    std::map<int, int> hist;
    for (int n = 0; n < 100000; ++n) {
        ++hist[round(dist(e2))];
    }

    for ( std::map<int, int>::const_iterator i = hist.begin(); i != hist.end(); ++i ) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << i->first << ' ' << std::string(i->second/200, '*') << '\n';
    }
}