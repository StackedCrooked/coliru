#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

struct pnt
{
    char _name;
    int _type;
    bool _aux;
};

int extract(const pnt& p)
{
    return p._type;
}

int main()
{
    pnt a;a._type = 1; pnt b;b._type = 2; pnt c;c._type = 3;
    
    std::vector<pnt> pnts; pnts.push_back(a); pnts.push_back(b); pnts.push_back(c);
    
    std::vector<int> pntType;
    
    // Boost Bind
    std::transform(pnts.begin(), pnts.end(), std::back_inserter(pntType), &extract);
    
    std::copy(pntType.begin(), pntType.end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl; 
    pntType.clear();
    
    // Boost Lambda
    std::transform(pnts.begin(), pnts.end(), std::back_inserter(pntType), boost::bind(&pnt::_type, _1));
    
    std::copy(pntType.begin(), pntType.end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;
    pntType.clear();
    
    // Custom functor
    std::transform(pnts.begin(), pnts.end(), std::back_inserter(pntType), (&boost::lambda::_1)->*&pnt::_type);
    
    std::copy(pntType.begin(), pntType.end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;
    pntType.clear();
}
