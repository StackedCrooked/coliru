    #include <iostream>
    #include <boost/shared_ptr.hpp>
    using namespace std;
     
    int main() {
    boost::shared_ptr< int > x(new int(5));
    if (x)
        cout << (*x) << endl;
    return 0;
    }