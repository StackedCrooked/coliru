#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
 
int main()
{
    std::v<int> v(10, 2);
    //std::vector<int> v(10, 2);
    //std::partial_sum(v.cbegin(), v.cend(), v.begin());
    //std::cout << "Among the numbers: ";
    //std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    //std::cout << '\n';
 
    //if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
      //  std::cout << "All numbers are even\n";
    //}
    
    if (all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
    cout << "Todos los numeros son pares" << endl;
    }
    //if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
    //    std::cout << "None of them are odd\n";
    //}
    //struct DivisibleBy
    //{
      //  const int d;
        //DivisibleBy(int n) : d(n) {}
        //bool operator()(int n) const { return n % d == 0; }
    //};
 
    //if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
      //  std::cout << "At least one number is divisible by 7\n";
    //}
}

