#include <iostream>
#include <functional>

#define VER 0

#if VER == 0
#define FIRST int
#define SECOND std::function<int(int)>
#else
#define FIRST auto
#define SECOND auto
#endif

auto terminal = [](FIRST term)       // <---------+  
{                                    //           |
    return [=] (SECOND func)         //           |  ???
    {                                //           |
        return terminal(func(term)); // >---------+
    };
};

int main()
{
    terminal(2)( [](int x) { std::cout << x << "\n"; return x; } );
}