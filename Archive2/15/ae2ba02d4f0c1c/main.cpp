#include <string>
#include <iostream>
#include <boost/test/floating_point_comparison.hpp>
using namespace std;
using namespace boost;

 
int main(){
    using namespace boost::test_tools;
    
    cout << close_at_tolerance(1000, 1000.0001, 0.0001) << endl;
}
