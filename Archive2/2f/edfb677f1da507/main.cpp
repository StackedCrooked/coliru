#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace details
{
    template <size_t N>
    class FizzBuzzImpl;
    
    
    template<size_t N, bool MultThree, bool MultFive>
    class FizzBuzzImplPrint : FizzBuzzImpl<N-1>
    {
    public:
        FizzBuzzImplPrint()
        {
            std::cout << N << std::endl;
        }
    };
    
    template<size_t N>
    class FizzBuzzImplPrint<N, true, true> : FizzBuzzImpl<N-1>
    {
    public:
        FizzBuzzImplPrint()
        {
            std::cout << "FizzBuzz" << std::endl;
        }
    };
    
    
    template<size_t N>
    class FizzBuzzImplPrint<N, true, false> : FizzBuzzImpl<N-1>
    {
    public:
        FizzBuzzImplPrint()
        {
            std::cout << "Fizz" << std::endl;
        }
    };
    
    
    template<size_t N>
    class FizzBuzzImplPrint<N, false, true> : FizzBuzzImpl<N-1>
    {
    public:
        FizzBuzzImplPrint()
        {
            std::cout << "Buzz" << std::endl;
        }
    };
    
    template <size_t N>
    class FizzBuzzImpl : public FizzBuzzImplPrint<N, (N % 3) == 0,  (N % 5) == 0>
    {};
    
    template <>
    class FizzBuzzImpl<0>
    {};
    
}


template <size_t N>
class FizzBuzz : public details::FizzBuzzImpl<N>
{};


int main()
{
    FizzBuzz<100> p;
    return 0;
}
