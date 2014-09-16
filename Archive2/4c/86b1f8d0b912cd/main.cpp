#include <iostream>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

using namespace std;

int main() {
    int64_t y = 123;
    try {
        y = boost::numeric_cast<int64_t>(std::numeric_limits<double>::max());
    }
    catch (boost::numeric::bad_numeric_cast const& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "y = " << y << endl;
    
    y = 123;
    try {
        y = boost::numeric_cast<int64_t>(std::numeric_limits<double>::infinity());
    }
    catch (boost::numeric::bad_numeric_cast const& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "y = " << y << endl;
    
    y = 123;
    try {
        y = boost::numeric_cast<int64_t>(std::numeric_limits<double>::signaling_NaN());
    }
    catch (boost::numeric::bad_numeric_cast const& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "y = " << y << endl;

    return 0;
}