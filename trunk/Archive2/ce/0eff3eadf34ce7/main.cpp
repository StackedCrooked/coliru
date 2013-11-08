#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

template <int n>
struct fac {
    enum { value = n * fac<n - 1>::value };
};
 
template <>
struct fac<0> {
    enum { value = 1 };
};

int main() {
    //! Set timer
    typedef std::chrono::time_point<std::chrono::system_clock> Clock;
    Clock start, end;
    start = std::chrono::system_clock::now();
    
    
    //! Calculate the factorial for N
    cout << fac<0>::value << ",";
    cout << fac<2>::value << ",";
    cout << fac<4>::value << ",";
    cout << fac<6>::value << ",";
    cout << fac<8>::value << ",";
    cout << fac<10>::value << ",";
    cout << fac<12>::value << ",";
    
    //! Calculate passed time and print the result
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << endl << "Elapsed time: " << elapsed_seconds.count() << endl;
}