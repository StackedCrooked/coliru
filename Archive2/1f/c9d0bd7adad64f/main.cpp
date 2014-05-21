#include <iostream>

using std::cout;
using std::endl;

const auto& e = [=]
    (const int n) { 
    cout << n << endl; 
};

int main()
try {
    e(2);
}
catch (std::exception& e) {}
