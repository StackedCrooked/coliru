#include <boost/coroutine/all.hpp>
#include <string>
#include <vector>


typedef boost::coroutines::coroutine<int(char)> coroutine_t;


void f(coroutine_t::caller_type & ca)
{
    std::vector<int> vec = {1, 2, 3};
    for (int i : vec)
    {
        char c = ca.get();
        std::cout << "c: " << c << std::endl;
        ca(i);
    }
}

int main()
{
    coroutine_t cr(f);
    std::string str("abc");
    for (char c : str)
    {
        std::cout << c << std::flush;
        cr(c);
        int n = cr.get();
        std::cout << n << std::endl;        
    }
}


