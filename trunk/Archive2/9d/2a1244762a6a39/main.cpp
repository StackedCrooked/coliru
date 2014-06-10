#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/icl/interval_set.hpp>

int main()
{
    using namespace boost::icl;

    // whole path interval
    interval_set<int> pathUnsentIntervals;
    pathUnsentIntervals += discrete_interval<int>(0, 1000);

    // subtract a sent interval
    pathUnsentIntervals -= discrete_interval<int>(0, 300);

    // interval for current path sections
    interval_set<int> pathSectionsInterval;
    pathSectionsInterval += discrete_interval<int>(100, 600);
    
    // unsent interval for the current path sections
    interval_set<int> pathSectionsUnsentIntervals = pathUnsentIntervals & pathSectionsInterval;
    
    std::cout << "Intervals left:\n";
    for (interval_set<int>::iterator it = pathSectionsUnsentIntervals.begin(); it != pathSectionsUnsentIntervals.end(); ++it)
        std::cout << *it << std::endl;
    
    

}
