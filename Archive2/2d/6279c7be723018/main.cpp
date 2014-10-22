#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>

struct Bla {};

struct Test
{
    Test() : x(0), str(), bla() { std::cout << "Test( void )\n"; }
    
    template<typename HeadArg, typename... TailArgs>
    Test(HeadArg&& head, TailArgs&&... tail) : 
        Test(std::forward<TailArgs>(tail)...)
    {
        std::cout << "Test( " << typeid(head).name() << ", ... )\n";
        set_argument(head);
    }
    
    template<typename Arg> void set_argument(const Arg& arg) { static_assert(typeid(Arg) == typeid(int) || typeid(Arg) == typeid(std::string), "no argument with that type");}
    
    int x;
    std::string str;
    Bla bla;
};
template<> void Test::set_argument(const int& arg) {x = arg;std::cout << ">set x\n";}
template<> void Test::set_argument(const std::string& arg) {str = arg;}
template<> void Test::set_argument(const Bla& arg) {bla = arg;}


int main()
{
    Test test;
    
    test = Test(-123, std::string("test"), Bla());
    std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    test = Test(std::string("test"), -123, Bla());
    std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    test = Test(std::string("test"), Bla(), -123);
    std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    test = Test(Bla(), -123, std::string("test"));
    std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    test = Test(Bla(), std::string("test"), -123);
    std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    //test = Test(-321.0f, std::string("test"));
    //std::cout << "str: '" << test.str << "', x: " << test.x << "\n";
    
    
    
}
