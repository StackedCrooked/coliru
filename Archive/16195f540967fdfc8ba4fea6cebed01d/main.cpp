#include <iostream>
#include <memory>
#include <tuple>
 
 
struct Dynamic
{
    virtual ~Dynamic() {}
};
 
template<typename A, typename B>
struct Generic : Dynamic
{
    Generic()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};
 
 
template<typename A, typename B>
std::unique_ptr<Dynamic> Make()
{
    return std::unique_ptr<Dynamic>(new Generic<A, B>());
}
 
 
template<typename A>
std::unique_ptr<Dynamic> Make(char b)
{
    switch (b)
    {
        case 'i':
        {
            return Make<A, int>();
        }
        case 'u':
        {
            return Make<A, unsigned>();
        }
        default: throw 0;
    }
}
 
 
std::unique_ptr<Dynamic> Make(char a, char b)
{
    switch (a)
    {
        case 'i':
        {
            return Make<int>(b);
        }
        case 'u':
        {
            return Make<unsigned>(b);
        }
        default: throw 0;
    }
}
 
 
int main()
{
    Make('i', 'i');
    Make('i', 'u');aa
    Make('u', 'i');
    Make('i', 'i');
}