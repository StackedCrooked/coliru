#include <vector>
#include <cstdlib>
#include <algorithm>

void error_check() {}

int main()
{
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), [](){ //either add -> int, 
        error_check(); //or comment this out to compile
        return rand()%99; });
}
