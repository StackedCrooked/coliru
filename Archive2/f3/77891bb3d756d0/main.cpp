#include <iostream>
#include <string>
#include <vector>

namespace client
{
    struct Button{};
    struct Window{};
    struct None;
    
    template<typename T, typename T1, typename T2>
    struct select
    {
        typedef None type;
    };
    
    template<typename T, typename T2>
    struct select<T, T, T2>
    {
        typedef T type;
    };
    
    template<typename T, typename T1>
    struct select<T, T1, T>
    {
        typedef T type;
    };
    
    template<typename T1 = None, typename T2 = None >
    struct Factory
    {        
        typedef typename select<Window, T1, T2>::type window_type; 
        typedef typename select<Button, T1, T2>::type button_type; 
    
        template<typename T>
        static T*
        create(typename std::enable_if<std::is_same<T, window_type>::value ||
                                       std::is_same<T, button_type>::value>::type* = 0)
        {
            return new T;
        }
    };
}

int main()
{
    auto w = client::Factory<client::Window>::create<client::Button>();
}
