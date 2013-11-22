#include <boost/range/combine.hpp>
#include <iostream>

int main()
{
    using namespace boost;
    using namespace std;
    
    int x[3] = {1,2,3};
    double y[3] = {1.1, 2.2, 3.3};
    
    for(const auto &p : combine(x,y))
        cout << get<0>(p) << " " << get<1>(p) << endl;
}