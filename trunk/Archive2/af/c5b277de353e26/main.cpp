#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

int main()
{
    boost::shared_ptr<int> ptr1(new int(5));
    boost::shared_ptr<int> ptr2();
    
    if(!ptr1) cout << "1" << endl;
    if(!ptr2) cout << "2" << endl;
    
    return 0;
}