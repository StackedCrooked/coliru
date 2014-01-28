#include <limits>
#include <iostream>

using namespace std;
 
int main()
{
    std::cout << std::numeric_limits<long long int>::max() << std::endl;
    std::cout << "9223372036854775808";
}