#include <boost/coroutine/all.hpp>
#include <string>
#include <vector>


typedef boost::coroutines::coroutine<int(char)> Coroutine;


void f(Coroutine::caller_type & ca)
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
    Coroutine theCoroutine(f);
    std::string str("abc");
    for (char c : str)
    {
        std::cout << c << std::flush;
        theCoroutine(c);
        int n = theCoroutine.get();
        std::cout << n << std::endl;        
    }
}