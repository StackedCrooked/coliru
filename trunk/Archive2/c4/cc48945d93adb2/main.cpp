// use captured variables
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
const long Size = 390000L;


int main()
{
    using std::cout;
    std::vector<int> numbers(Size);
    std::srand(std::time(0));
    std::generate(numbers.begin(), numbers.end(), std::rand);
    cout << "Sample size = " << Size << '\n';
    
    int count13 = 0;
    std::count_if(numbers.begin(), numbers.end(),
        [&count13](int x){ return (count13 += x % 13) == 0; });
    cout << "count of number divisible by 13: " << count13 << '\n';
    return 0;
}