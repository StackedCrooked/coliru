#include <boost/test/included/prg_exec_monitor.hpp> 
#include <boost/test/execution_monitor.hpp>
#include <iostream>
#include <vector>
 
using namespace std;

int test()
{
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    vector<int>::iterator iter = vec.begin();
    cout << *(iter+10000000) << "\n";
    return 0;
}

int cpp_main( int, char* [] )
{
    boost::execution_monitor m;
    try
    {
        m.execute(test);
    }
    catch ( boost::execution_exception const& ex )
    {
        cout << "Caught exception: " << ex.what() << endl;
    }
    cout << "Alive!" << endl;
    return 0;
}