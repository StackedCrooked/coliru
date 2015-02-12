#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <numeric>

//return a vector of prime numbers from 1 to N
// for, do-while, while, and loop constructs are not allowed;
// recursion is not allowed as well,
std::vector<int> getPrimes(int N)
{
    std::vector<int> ans , temp(N-1);
    std::iota(temp.begin(),temp.end(),2);
    
    std::copy_if(temp.begin(),temp.end(),std::back_inserter(ans),[](int x){
        //x is not divisible by numbers lower than it or if 
        std::vector<int> calc(x-1);
        std::iota(calc.begin(),calc.end(),2);
        
        //calc.erase(std::remove(calc.begin(),calc.end(),x));
        //std::copy(calc.begin(),calc.end(),std::ostream_iterator<int>(std::cout," "));
       // std::cout<< std::endl;
        if (std::all_of(calc.begin(),calc.end(),[x](int y){ 
            if(x==y)
                return false;
            else
                return !(x%y);
        }));
    });
 //   std::copy(ans.begin(),ans.end(),std::ostream_iterator<int>(std::cout," "));
    return ans;
}


int main()
{
    auto noPrimes = getPrimes(1);
    decltype(noPrimes) noPrimesExpected = {};
    assert(noPrimes == noPrimesExpected);

    const int N = 100;
    auto result = getPrimes(N);
    decltype(result) expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    assert(expected == result);
}
