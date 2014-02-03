#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <memory>
 
// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t) 
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1>{
    static void print(const Tuple& t) 
    {
        std::cout << std::get<0>(t);
    }
};
 
template<class... Args>
void print(const std::tuple<Args...>& t) 
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}
// end helper function
 
int main()
{
    std::tuple<int, std::string, double> t1;
    std::cout << "Value-initialized: "; print(t1);
    std::tuple<int, std::string, double> t2(42, "Test", -3.14);
    std::cout << "Initialized with values: "; print(t2);
    std::tuple<char, std::string, int> t3(t2);
    std::cout << "Implicitly converted: "; print(t3);
    std::tuple<int, double> t4(std::make_pair(42, 3.14));
    std::cout << "Constructed from a pair"; print(t4);
 
    // given Allocator my_alloc with a single-argument constructor my_alloc(int)
    // use my_alloc(1) to allocate 10 ints in a vector
    std::vector<int, my_alloc> v(10, 1, my_alloc(1));
    // use my_alloc(2) to allocate 10 ints in a vector in a tuple
    std::tuple<int, std::vector<int, my_alloc>, double> t5(std::allocator_arg,
                                                           my_alloc(2), 42, v,  -3.14);
}