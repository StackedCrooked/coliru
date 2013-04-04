#include <vector>

const int c = 0;
volatile int x = 0;

int main()
{        
    std::vector<int> vec;
    vec.emplace_back(x);
    vec.push_back(c);
    vec.push_back(x); // error: no matching function for call to 'std::vector<int>::push_back(volatile int&)'

}//a